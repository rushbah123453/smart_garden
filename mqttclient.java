package com.example.rushabh.hello;

import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.media.Ringtone;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Vibrator;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.app.NotificationCompat;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class MainActivity extends AppCompatActivity {

    static String MQTTHOST="tcp://broker.mqttdashboard.com:1883";//examle "tcp://192.168.1.7:1883"
    static String Username="led";
    static String Password="led";
    String topicstr="my/topic2";
    private static TextView text;
    MqttAndroidClient client;
    MqttConnectOptions options;
    Vibrator vibrator;
    Ringtone myring;
    static String msg;
    public static double x,y;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        text=(TextView) findViewById(R.id.text);//for subscribtion,incoming data is displayd here
       // vibrator=(Vibrator)getSystemService(VIBRATOR_SERVICE);
        Uri uri= RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
        myring=RingtoneManager.getRingtone(getApplicationContext(),uri);
        String clientId = MqttClient.generateClientId();
        //Button graph1=(Button)findViewById(R.id.seegraph);
        client = new MqttAndroidClient(this.getApplicationContext(),MQTTHOST, clientId);
        options = new MqttConnectOptions();
        //opts.setConnectionTimeout(240000);
        //options.setCleanSession(true);
        //options.setConnectionTimeout(3000);
        //options.setKeepAliveInterval(10 * 60);
        options.setUserName(Username);
        options.setPassword(Password.toCharArray());
        //text=(TextView) findViewById(R.id.text);
        //Toast.makeText(MainActivity.this,toString(text1),Toast.LENGTH_SHORT).show();

        try {
            Toast.makeText(MainActivity.this,"trying to connect_rushabh!",Toast.LENGTH_SHORT).show();
            IMqttToken token = client.connect(options);

            Toast.makeText(MainActivity.this,"token created ",Toast.LENGTH_SHORT).show();
            /*options.setKeepAliveInterval(6000 * 5);*/
            token.setActionCallback(new IMqttActionListener() {



                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // We are connected
                    Toast.makeText(MainActivity.this,"connect_rushabh!",Toast.LENGTH_SHORT).show();
                    subscribe();
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    // Something went wrong e.g. connection timeout or firewall problems
                    Toast.makeText(MainActivity.this,"failing_rushabh!",Toast.LENGTH_SHORT).show();

                }
            });

        } catch (MqttException e) {
            e.printStackTrace();
        }


        client.setCallback(new MqttCallback() {
            @Override
            public void connectionLost(Throwable cause) {

            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                text.setText(msg=new String(message.getPayload()));
               // x=Double.parseDouble(msg);
                //vibrator.vibrate(650);
                //notifynew();
                //myring.play();



            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {

            }
        });
    }

    public void pub(View v){
        String topic = topicstr;
        String message= "Rushabh";

        try {
            Toast.makeText(MainActivity.this, "inside publish method", Toast.LENGTH_SHORT).show();
            client.publish(topic, message.getBytes(),0,false);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }


    public void subscribe()
    {
        try{
            client.subscribe(topicstr,0);
        }
        catch(MqttException e)
        {
            e.printStackTrace();
        }
    }

    public void conn(View v)
    {


        try {
            Toast.makeText(MainActivity.this,"trying to connect_rushabh!",Toast.LENGTH_SHORT).show();
            IMqttToken token = client.connect(options);

            // Toast.makeText(MainActivity.this,"token created ",Toast.LENGTH_SHORT).show();
            /*options.setKeepAliveInterval(6000 * 5);*/
            token.setActionCallback(new IMqttActionListener() {



                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // We are connected
                    Toast.makeText(MainActivity.this,"connect_rushabh!",Toast.LENGTH_SHORT).show();
                    subscribe();
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    // Something went wrong e.g. connection timeout or firewall problems
                    Toast.makeText(MainActivity.this,"failing_rushabh!",Toast.LENGTH_SHORT).show();

                }
            });

        } catch (MqttException e) {
            e.printStackTrace();
        }



    }

    public void disconn(View v)
    {

        try {
            Toast.makeText(MainActivity.this,"trying to disconnect_rushabh!",Toast.LENGTH_SHORT).show();
            IMqttToken token = client.disconnect();

            Toast.makeText(MainActivity.this,"token created ",Toast.LENGTH_SHORT).show();
            /*options.setKeepAliveInterval(6000 * 5);*/
            token.setActionCallback(new IMqttActionListener() {



                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // We are connected
                    Toast.makeText(MainActivity.this,"disconnected_rushabh!",Toast.LENGTH_SHORT).show();
                    //   subscribe();
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    // Something went wrong e.g. connection timeout or firewall problems
                    Toast.makeText(MainActivity.this,"failed_to_disconnect_rushabh!",Toast.LENGTH_SHORT).show();

                }
            });

        } catch (MqttException e) {
            e.printStackTrace();
        }


    }
    public void notifynew()
    {


        NotificationCompat.Builder notificationbuilder=(NotificationCompat.Builder)new NotificationCompat.Builder(MainActivity.this)
                .setDefaults(NotificationCompat.DEFAULT_ALL)
                //.setSmallIcon(R.drawable.w)
                //.setLargeIcon(BitmapFactory.decodeResource(getResources(),R.drawable.w))
                .setContentText("PLEASE WATER YOUR PLANTS")
                .setContentText("Humidity level of soild is"+" "+msg+"%");

        NotificationManager notificationManager=(NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.notify(1,notificationbuilder.build());



    }

    public void graph(View view)
    {
        /*//Intent intent=new Intent(this,raph.class);
        Bundle b = new Bundle();
        b.putDouble("key",x);
        intent.putExtras(b);
        startActivity(intent);*/

    }

}
