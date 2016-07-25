package com.purdue.e_rccar.Gyro;

import android.app.Service;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.IBinder;
import android.util.Log;

import com.purdue.e_rccar.MainActivity;
import com.purdue.e_rccar.ModeSelectActivity;

/**
 * Created by Jimin on 2015-07-21.
 */
public class GyroService extends Service implements SensorEventListener {

    private static final String TAG = "GyroService";
    // 센서 관리자
    public static SensorManager sm = null;
    // 방향 센서
    Sensor oriSensor = null;

    ModeSelectActivity msa = new ModeSelectActivity();

    @Override
    public IBinder onBind(Intent arg0) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.e(TAG, "onStartCommand");
        super.onStartCommand(intent, flags, startId);
        return START_STICKY;
    }

    @Override
    public void onCreate() {
        Log.e(TAG, "onCreate");

        // SensorManager 인스턴스를 가져옴
        sm = (SensorManager) getSystemService(SENSOR_SERVICE);
        // 방향 센서
        oriSensor = sm.getDefaultSensor(Sensor.TYPE_ORIENTATION);

        // 방향 센서 리스너 오브젝트를 등록
        sm.registerListener(this, oriSensor, SensorManager.SENSOR_DELAY_NORMAL);
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // TODO Auto-generated method stub
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.values[2] < 20.0) {
            msa.sendData(getApplicationContext(), 'a');
        } else {
            msa.sendData(getApplicationContext(), 'b');
        }
    }

    @Override
    public void onDestroy() {
        Log.e(TAG, "onDestroy");
        super.onDestroy();

        // 센서에서 이벤트 리스너 분리
        sm.unregisterListener(this);

        stopSelf();
    }
}