package it.unibo.seiot.gm.smartdumpsterapp.app;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Objects;
import java.util.Optional;
import java.util.UUID;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
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
    private static final int CORE_POOL_SIZE = 1;
    private static final long KEEP_ALIVE_PERIOD = 90L;
    private static final String BT_TARGET_NAME = "bl-arduino";
    private static final String REQUESTING_STR = "Richiesta in corso";
    private static final String TAG = "SmartDumpsterApp_Main";
    private static final String CONNECTED_STR = "connesso";
    private static final String NOT_CONNECTED_STR = "non connesso";
    private static final String REQUEST_ERROR_STR = "Errore, chiudi l'app e riprova. Potrebbe esssere necessario aspettare " +
            "alcuni minuti";
    private static final String COMM_SERVICE_ERROR = "Impossibile comunicare il server, il deposito sará bloccato. Riprova tra " +
            "cinque minuti";
    private static final String NO_TOKEN = "";
    private static final String WAIT_FOR_SERVER_STR = "In attesa di comunicazione con il server";

    private Optional<BluetoothChannel> btChannel;
    private String token;
    private ScheduledThreadPoolExecutor keepAliveExecutor;
    private int failuresCount;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.token = NO_TOKEN;
        /* activate bluetooth */
        btChannel = Optional.empty();
        this.activateBT();
        /* init UI */
        this.initUI();
        /* init keepAliveExecutor */
        this.initKeepAliveExecutor();
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
        this.disconnectBt();
    }

    @Override
    public void onPause() {
        super.onPause();
        this.disconnectBt();
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
        final Button connectBtn = findViewById(R.id.connectButton);
        connectBtn.setOnClickListener(this::blConnect);
        /* Request token button */
        final Button tokenBtn = findViewById(R.id.askTokenButton);
        tokenBtn.setEnabled(true);
        tokenBtn.setOnClickListener(this::requestToken);
        /* Trash type 1 button */
        final Button trash1Btn = findViewById(R.id.trashType1Button);
        trash1Btn.setEnabled(false);
        trash1Btn.setOnClickListener(v -> this.sendTrashTypeMessage(ControllerMessage.TRASH_1_SET_MESSAGE));
        /* Trash type 2 button */
        final Button trash2Btn = findViewById(R.id.trashType2Button);
        trash2Btn.setEnabled(false);
        trash2Btn.setOnClickListener(v -> this.sendTrashTypeMessage(ControllerMessage.TRASH_2_SET_MESSAGE));
        /* Trash type 3 button */
        final Button trash3Btn = findViewById(R.id.trashType3Button);
        trash3Btn.setEnabled(false);
        trash3Btn.setOnClickListener(v -> this.sendTrashTypeMessage(ControllerMessage.TRASH_3_SET_MESSAGE));
        /* Keep open button */
        final Button keepOpenButton = findViewById(R.id.keepOpenButton);
        keepOpenButton.setEnabled(false);
        keepOpenButton.setOnClickListener(this::askKeepOpen);
    }

    private void blConnect(final View v) {
        this.activateBT(); // should already be active, but just to be sure
        try {
            final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(BT_TARGET_NAME);
            final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
            final BluetoothChannel.Listener listener
                    = new RealBluetoothChannel.Listener() {
                        @Override
                        public void onMessageReceived(final String receivedMessage) {
                            // the terminator of the arduino message is usually a carriage return
                            final String parsedMessage = receivedMessage.chars()
                                                                        .filter(c -> c != 13 && c != 10)
                                                                        .mapToObj(c -> Character.toString((char) c))
                                                                        .collect(Collectors.joining());
                            if (parsedMessage.equals(ControllerMessage.STOP_DEPOSIT.getMessage())) {
                                Log.d(TAG, "End deposit");
                                // stopping keep alive messages
                                keepAliveExecutor.shutdownNow();
                                // resetting ScheduledThreadPoolExecutor for future necessities
                                initKeepAliveExecutor();
                                // signalling end of deposit
                                final ServiceMessageBuilder builder = new ServiceMessageBuilder(ServiceMessageType.STOP_DEPOSIT);
                                builder.setToken(token)
                                       .setDepositPhase("end")
                                       .build()
                                       .send(p -> {
                                           findViewById(R.id.keepOpenButton).setEnabled(false);
                                           disableTrashButtons();
                                           // the deposit ended, a new token can be requested
                                           resetToken();
                                       });
                            } else {
                                Log.d(TAG, "received ASCII " + receivedMessage.chars().boxed().collect(Collectors.toList()));
                            }
                        }
                        @Override
                        public void onMessageSent(final String sentMessage) {
                            // no action needed when a message is sent
                            Log.d(TAG, sentMessage);
                        }
                    };
            final ConnectionTask.EventListener eventListener =
                    new ConnectionTask.EventListener() {
                        @Override
                        public void onConnectionActive(final BluetoothChannel channel) {
                            btChannel = Optional.ofNullable(channel); // can't be sure null will not be passed as parameter
                            btChannel.ifPresent(c -> {
                                c.registerListener(listener);
                                ((TextView) findViewById(R.id.btStatus)).setText(CONNECTED_STR);
                                findViewById(R.id.connectButton).setEnabled(false);
                                if (!token.equals(NO_TOKEN)) {
                                    setEnableTrashButtons(true);
                                }
                            });
                        }
                        @Override
                        public void onConnectionCanceled() {
                            Log.d(TAG, "BT connection canceled");
                            disconnectBt();
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
        ((TextView) findViewById(R.id.errorText)).setText("");
        ((TextView) findViewById(R.id.tokenText)).setText(REQUESTING_STR);
        new ServiceMessageBuilder(ServiceMessageType.GET_TOKEN).build().send(this::tokenRequestAnswerManager);
    }

    private void askKeepOpen(final View v) {
        this.btChannel.ifPresent(c -> c.sendMessage(ControllerMessage.KEEP_OPEN_MESSAGE.getMessage()));
    }

    private void sendTrashTypeMessage(final ControllerMessage type) {
        // the deposit started, the trash type can't be changed
        Log.d(TAG, "Start deposit");
        ((TextView) findViewById(R.id.errorText)).setText(WAIT_FOR_SERVER_STR);
        final ServiceMessageBuilder builder = new ServiceMessageBuilder(ServiceMessageType.START_DEPOSIT);
        builder.setToken(token)
               .setDepositPhase("begin")
               .build()
               .send(p -> this.startDepositAnswerManager(p, type));
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
              .map(o -> (Button) o)
              .forEach(b -> b.setEnabled(set));
    }

    private boolean isOkCode(final int code) {
        return code >= 200 && code < 300;
    }

    private void resetToken() {
        this.token = NO_TOKEN;
        ((TextView) findViewById(R.id.tokenText)).setText(this.token);
        findViewById(R.id.askTokenButton).setEnabled(true);
    }

    private void startDepositAnswerManager(final Optional<Pair<Integer, String>> p, final ControllerMessage type) {
        if (p.isPresent() && isOkCode(p.get().first)) {
            // deposit start correctly communicated to the service
            this.disableTrashButtons();
            ((TextView) findViewById(R.id.errorText)).setText("");
            this.btChannel.ifPresent(c -> c.sendMessage(type.getMessage()));
            findViewById(R.id.keepOpenButton).setEnabled(true);
            this.failuresCount = 0;
            keepAliveExecutor.scheduleAtFixedRate(this::keepAliveTask, KEEP_ALIVE_PERIOD, KEEP_ALIVE_PERIOD, TimeUnit.SECONDS);
        } else {
            // connection didn't go well, needs to:
            // - stop deposit, because it can't be tracked
            // - allow for new token request
            this.btChannel.ifPresent(c -> c.sendMessage(ControllerMessage.PREMATURE_STOP_DEPOSIT.getMessage()));
            ((TextView) findViewById(R.id.errorText)).setText(COMM_SERVICE_ERROR);
            this.disableTrashButtons();
            this.resetToken();
            keepAliveExecutor.shutdownNow();
            initKeepAliveExecutor();
        }
    }

    private void tokenRequestAnswerManager(final Optional<Pair<Integer, String>> op) {
        if (op.isPresent() && isOkCode(op.get().first)) {
            try {
                final JSONObject j = new JSONObject(op.get().second);
                final String s = j.optString("token");
                if (Objects.nonNull(s)) {
                    ((TextView) findViewById(R.id.tokenText)).setText(s);
                    this.token = s;
                    this.btChannel.ifPresent(c -> this.enableTrashButtons());
                    findViewById(R.id.askTokenButton).setEnabled(false);
                    Log.d(TAG, "token: " + this.token);
                } else {
                    ((TextView) findViewById(R.id.tokenText)).setText(NO_TOKEN);
                    Log.d(TAG, "No token received");
                }
            } catch (JSONException e) {
                Log.e(TAG, e.getMessage());
            }
        } else {
            ((TextView) findViewById(R.id.tokenText)).setText(NO_TOKEN);
            ((TextView) findViewById(R.id.errorText)).setText(REQUEST_ERROR_STR);
            Log.d(TAG, REQUEST_ERROR_STR);
        }
    }

    private void keepAliveTask() {
        final ServiceMessageBuilder builder = new ServiceMessageBuilder(ServiceMessageType.KEEP_DEPOSITING);
        builder.setToken(this.token)
               .setDepositPhase("continue")
               .build()
               .send(p -> {
                   if (!(p.isPresent() && isOkCode(p.get().first))) {
                       this.failuresCount++;
                   }
                   if (this.failuresCount > 1) {
                       this.btChannel.ifPresent(c -> c.sendMessage(ControllerMessage.PREMATURE_STOP_DEPOSIT.getMessage()));
                       this.keepAliveExecutor.shutdown();
                   }
               });
    }

    private void disconnectBt() {
        this.btChannel.ifPresent(BluetoothChannel::close);
        this.btChannel = Optional.empty();
        ((TextView) findViewById((R.id.btStatus))).setText(NOT_CONNECTED_STR);
        findViewById(R.id.connectButton).setEnabled(true);
    }

    private void initKeepAliveExecutor() {
        this.keepAliveExecutor = new ScheduledThreadPoolExecutor(CORE_POOL_SIZE);
        this.failuresCount = 0;
    }
}
