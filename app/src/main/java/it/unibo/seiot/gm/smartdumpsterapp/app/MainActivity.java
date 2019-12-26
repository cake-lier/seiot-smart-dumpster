package it.unibo.seiot.gm.smartdumpsterapp.app;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.Objects;
import java.util.Optional;
import java.util.UUID;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import it.unibo.seiot.gm.smartdumpsterapp.R;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.BluetoothChannel;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.BluetoothUtils;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.ConnectToBluetoothServerTask;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.ConnectionTask;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.RealBluetoothChannel;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.exceptions.BluetoothDeviceNotFound;

/**
 * The main activity of the app.
 */
public class MainActivity extends AppCompatActivity {

    private static final int ENABLE_BT_REQ = 1;
    private static final String BT_TARGET_NAME = "bl-arduino";
    private static final String REQUESTING_STR = "Richiesta in corso";
    private static final String TAG = "SmartDumpsterApp_Main";

    private Optional<BluetoothChannel> btChannel;
    private String token;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        /* activate bluetooth */
        btChannel = Optional.empty();
        activateBT();
        /* init UI */
        initUI();
    }

    @Override
    public void onActivityResult(int reqID, int res, Intent data) {
        super.onActivityResult(reqID, res, data);
        if (reqID == ENABLE_BT_REQ && res == Activity.RESULT_OK) {
            Log.d(TAG, "BT was enabled");
        } else if (reqID == ENABLE_BT_REQ && res == Activity.RESULT_CANCELED) {
            Log.d(TAG, "BT was not enabled");
        }
    }

    @Override
    public void onStop() {
        super.onStop();
        this.btChannel.ifPresent(BluetoothChannel::close);
    }

    private void activateBT() {
        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();
        if (btAdapter == null) {
            Log.e(TAG, "BT is not available on this device");
            finish();
        } else if (!btAdapter.isEnabled()) {
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), ENABLE_BT_REQ);
        }
    }

    private void initUI() {
        /* Connect button */
        final Button connectBtn = (Button) findViewById(R.id.connectButton);
        connectBtn.setOnClickListener(this::blConnect);
        /* Request token button */
        final Button tokenBtn = (Button) findViewById(R.id.askTokenButton);
        tokenBtn.setEnabled(true);
        tokenBtn.setOnClickListener(this::requestToken);
        /* Trash type 1 button */
        final Button trash1Btn = (Button) findViewById(R.id.trashType1Button);
        trash1Btn.setEnabled(false);
        trash1Btn.setOnClickListener(v -> this.sendTrashTypeMessage(ControllerMessage.TRASH_1_SET_MESSAGE));
        /* Trash type 2 button */
        final Button trash2Btn = (Button) findViewById(R.id.trashType2Button);
        trash2Btn.setEnabled(false);
        trash2Btn.setOnClickListener(v -> this.sendTrashTypeMessage(ControllerMessage.TRASH_2_SET_MESSAGE));
        /* Trash type 3 button */
        final Button trash3Btn = (Button) findViewById(R.id.trashType3Button);
        trash3Btn.setEnabled(false);
        trash3Btn.setOnClickListener(v -> this.sendTrashTypeMessage(ControllerMessage.TRASH_3_SET_MESSAGE));
        /* Keep open button */
        final Button keepOpenButton = (Button) findViewById(R.id.keepOpenButton);
        keepOpenButton.setEnabled(false);
        keepOpenButton.setOnClickListener(this::askKeepOpen);
    }

    private void blConnect(final View v) {
        activateBT();
        try {
            final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(BT_TARGET_NAME);
            final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
            final BluetoothChannel.Listener listener
                    = new RealBluetoothChannel.Listener() {
                        @Override
                        public void onMessageReceived(final String receivedMessage) {
                            // the terminator of the arduino message is a carriage return
                            final String parsedMessage = receivedMessage.replaceAll("(\\r|\\n)", "");
                            if (parsedMessage.equals(ControllerMessage.START_DEPOSIT.getMessage())) {
                                // the deposit started, the trash type can't be changed
                                final ServiceMessageBuilder builder = new ServiceMessageBuilder(ServiceMessageType.START_DEPOSIT);
                                builder.setToken(token)
                                       .setDepositPhase("begin")
                                       .build()
                                       .send(s -> {
                                           disableTrashButtons();
                                           ((Button) findViewById(R.id.askTokenButton)).setEnabled(false);
                                       }); // TODO: this "blocks" the app if the service doesn't respond
                            } else if (parsedMessage.equals(ControllerMessage.STOP_DEPOSIT.getMessage())) {
                                // the deposit ended, a new token can be requested
                                final ServiceMessageBuilder builder = new ServiceMessageBuilder(ServiceMessageType.START_DEPOSIT);
                                builder.setToken(token)
                                       .setDepositPhase("end")
                                       .build()
                                       .send(s -> {
                                           ((Button) findViewById(R.id.keepOpenButton)).setEnabled(false);
                                           ((Button) findViewById(R.id.askTokenButton)).setEnabled(true);
                                       }); // TODO: this "blocks" the app if the service doesn't respond
                            } else {
                                Log.d(TAG, "received ASCII " + receivedMessage.chars().boxed().collect(Collectors.toList()));
                            }
                        }
                        @Override
                        public void onMessageSent(final String sentMessage) {
                            // TODO: what to do when a message is sent
                            Log.d(TAG, sentMessage);
                        }
                    };
            final ConnectionTask.EventListener eventListener =
                    new ConnectionTask.EventListener() {
                        @Override
                        public void onConnectionActive(final BluetoothChannel channel) {
                            ((Button) findViewById(R.id.askTokenButton)).setEnabled(true);
                            btChannel = Optional.ofNullable(channel); // can't be sure null will not be passed as parameter
                            btChannel.ifPresent(c -> c.registerListener(listener));
                        }
                        @Override
                        public void onConnectionCanceled() {
                            // TODO: what to do when the connection is interrupted
                        }
                    };
            final ConnectToBluetoothServerTask connectTask = new ConnectToBluetoothServerTask(serverDevice, uuid, eventListener);
            connectTask.execute();
            Log.d(TAG, "Task for connecting to BT executed");
        } catch (final BluetoothDeviceNotFound e) {
            Log.e(TAG, "BT device " + BT_TARGET_NAME + " not found");
        }
    }

    private void requestToken(final View v) {
        ((TextView) findViewById(R.id.tokenText)).setText(REQUESTING_STR);
        new ServiceMessageBuilder(ServiceMessageType.START_DEPOSIT).setToken(token)
                                                                   .setDepositPhase("begin")
                                                                   .build()
                                                                   .send(j -> {
                                                                        final String s = j.optString("token");
                                                                        if (Objects.nonNull(s)) {
                                                                            ((TextView) findViewById(R.id.tokenText)).setText(s);
                                                                            this.token = s;
                                                                            this.enableTrashButtons();
                                                                        }
                                                                   });
    }

    private void askKeepOpen(final View v) {
        this.btChannel.ifPresent(c -> c.sendMessage(ControllerMessage.KEEP_OPEN_MESSAGE.getMessage()));
    }

    private void sendTrashTypeMessage(final ControllerMessage type) {
        this.btChannel.ifPresent(c -> c.sendMessage(type.getMessage()));
        ((Button) findViewById(R.id.keepOpenButton)).setEnabled(true);
    }

    private void enableTrashButtons() {
        setEnableTrashButtons(true);
    }

    private void disableTrashButtons() {
        setEnableTrashButtons(false);
    }

    private void setEnableTrashButtons(final boolean set) {
        Stream.of(R.id.trashType1Button, R.id.trashType2Button, R.id.trashType3Button)
              .map(this::findViewById)
              .map(o -> {return (Button) o;})
              .forEach(b -> b.setEnabled(set));
    }
}
