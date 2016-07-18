package com.purdue.e_rccar;

import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.purdue.e_rccar.Gyro.GyroService;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.UUID;

public class Mode2Activity extends Activity {

    ////////////////////////////////////For Layout//////////////////////////////////////
    /**
     * ImageButton
     */
    ImageButton btn_middle;
    ImageButton btn_left1;
    ImageButton btn_left2;
    ImageButton btn_left3;
    ImageButton btn_right1;
    ImageButton btn_right2;
    ImageButton btn_right3;
    ImageButton btn_start;
    ImageButton btn_stop;
    ImageButton btn_step1;
    ImageButton btn_step2;
    ImageButton btn_step3;
    ImageButton btn_step4;
    ImageButton btn_step5;
    ////////////////////////////////////////////////////////////////////////////////////

    ModeSelectActivity msa = new ModeSelectActivity();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mode2);

        btn_middle = (ImageButton) findViewById(R.id.btn_middle);
        btn_middle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "middle");
            }
        });
        btn_left1 = (ImageButton) findViewById(R.id.btn_left1);
        btn_left1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "left1");
            }
        });
        btn_left2 = (ImageButton) findViewById(R.id.btn_left2);
        btn_left2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "left2");
            }
        });
        btn_left3 = (ImageButton) findViewById(R.id.btn_left3);
        btn_left3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "left3");
            }
        });

        btn_right1 = (ImageButton) findViewById(R.id.btn_right1);
        btn_right1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "right1");
            }
        });
        btn_right2 = (ImageButton) findViewById(R.id.btn_right2);
        btn_right2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "right2");
            }
        });
        btn_right3 = (ImageButton) findViewById(R.id.btn_right3);
        btn_right3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "right3");
            }
        });

        btn_start = (ImageButton) findViewById(R.id.btn_start);
        btn_start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //sendData(getApplicationContext(), "stop");
                startService(new Intent(getApplicationContext(), GyroService.class));
            }
        });

        btn_stop = (ImageButton) findViewById(R.id.btn_stop);
        btn_stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "stop");
            }
        });

        btn_step1 = (ImageButton) findViewById(R.id.btn_step1);
        btn_step1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "step1");
            }
        });

        btn_step2 = (ImageButton) findViewById(R.id.btn_step2);
        btn_step2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "step2");
            }
        });

        btn_step3 = (ImageButton) findViewById(R.id.btn_step3);
        btn_step3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "step3");
            }
        });

        btn_step4 = (ImageButton) findViewById(R.id.btn_step4);
        btn_step4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "step4");
            }
        });

        btn_step5 = (ImageButton) findViewById(R.id.btn_step5);
        btn_step5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), "step5");
            }
        });
    }

    // onDestroy() : 어플이 종료될때 호출 되는 함수.
    //               블루투스 연결이 필요하지 않는 경우 입출력 스트림 소켓을 닫아줌.
    @Override
    protected void onDestroy() {
        super.onDestroy();
        stopService(new Intent(getApplicationContext(), GyroService.class));
        try {
        } catch (Exception e) {
        }
    }
}
