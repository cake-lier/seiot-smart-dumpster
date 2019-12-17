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

import java.util.UUID;

import it.unibo.seiot.gm.smartdumpsterapp.R;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.BluetoothChannel;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.BluetoothUtils;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.ConnectToBluetoothServerTask;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.ConnectionTask;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.RealBluetoothChannel;
import it.unibo.seiot.gm.smartdumpsterapp.btlib.exceptions.BluetoothDeviceNotFound;

// TODO: manage http connection
// TODO: which messages can be received with bluetooth?
public class MainActivity extends AppCompatActivity {

    private static final int ENABLE_BT_REQ = 1;
    private static final String BT_TARGET_NAME = "bl-arduino";
    private static final String TRASH_1_SET_MESSAGE = "A";
    private static final String TRASH_2_SET_MESSAGE = "B";
    private static final String TRASH_3_SET_MESSAGE = "C";

    private BluetoothChannel btChannel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        /* activate bluetooth */
        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();
        if (btAdapter == null) {
            Log.e("Smart Dumpster App", "BT is not available on this device");
            finish();
        }
        if (!btAdapter.isEnabled()) {
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), ENABLE_BT_REQ);
        }
        /* init UI */
        initUI();
    }

    @Override
    public void onActivityResult(int reqID, int res, Intent data) {
        super.onActivityResult(reqID, res, data);
        if (reqID == ENABLE_BT_REQ && res == Activity.RESULT_OK) {
            Log.d("Smart Dumpster App", "BT was enabled");
        } else if (reqID == ENABLE_BT_REQ && res == Activity.RESULT_CANCELED) {
            Log.d("Smart Dumpster App", "BT was not enabled");
        }
    }

    @Override
    public void onStop() {
        super.onStop();
        this.btChannel.close();
    }

    private void initUI() {
        /* Token text */
        final TextView tokenText = (TextView) findViewById(R.id.tokenText);
        tokenText.setOnClickListener(this::blConnect);
        /* Connect button */
        final Button connectBtn = (Button) findViewById(R.id.connectButton);
        connectBtn.setOnClickListener(this::blConnect);
        /* Request token button */
        final Button tokenBtn = (Button) findViewById(R.id.askTokenButton);
        tokenBtn.setEnabled(false);
        tokenBtn.setOnClickListener(this::requestToken);
        /* Trash type 1 button */
        final Button trash1Btn = (Button) findViewById(R.id.trashType1Button);
        trash1Btn.setEnabled(false);
        trash1Btn.setOnClickListener(this::setTrashType1);
        /* Trash type 2 button */
        final Button trash2Btn = (Button) findViewById(R.id.trashType2Button);
        trash2Btn.setEnabled(false);
        trash2Btn.setOnClickListener(this::setTrashType2);
        /* Trash type 3 button */
        final Button trash3Btn = (Button) findViewById(R.id.trashType3Button);
        trash3Btn.setEnabled(false);
        trash3Btn.setOnClickListener(this::setTrashType3);
    }

    private void blConnect(final View v) {
        try {
            final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(BT_TARGET_NAME);
            final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
            final ConnectionTask.EventListener eventListener =
                    new ConnectionTask.EventListener() {
                        @Override
                        public void onConnectionActive(final BluetoothChannel channel) {
                            ((Button) findViewById(R.id.askTokenButton)).setEnabled(true);
                            btChannel = channel;
                            btChannel.registerListener(new RealBluetoothChannel.Listener() {
                                                            @Override
                                                            public void onMessageReceived(String receivedMessage) {
                                                                // TODO: what to do when a message is received
                                                                // when the message is the token set tokenView to token
                                                            }
                                                            @Override
                                                            public void onMessageSent(String sentMessage) {
                                                                // TODO: what to do when a message is sent
                                                            }
                                                        });
                        }
                        @Override
                        public void onConnectionCanceled() {
                            // TODO: what to do when the connection is interrupted
                        }
                    };
            final ConnectToBluetoothServerTask connectTask = new ConnectToBluetoothServerTask(serverDevice, uuid, eventListener);
            connectTask.execute();
        } catch (final BluetoothDeviceNotFound e) {
            Log.e("Smart Dumpster App", "BT device " + BT_TARGET_NAME + " found");
        }
    }

    private void requestToken(final View v) {
        // TODO: send token request message via http
    }

    private void setTrashType1(final View v) {
        this.btChannel.sendMessage(TRASH_1_SET_MESSAGE);
    }

    private void setTrashType2(final View v) {
        this.btChannel.sendMessage(TRASH_2_SET_MESSAGE);
    }

    private void setTrashType3(final View v) {
        this.btChannel.sendMessage(TRASH_3_SET_MESSAGE);
    }
}
