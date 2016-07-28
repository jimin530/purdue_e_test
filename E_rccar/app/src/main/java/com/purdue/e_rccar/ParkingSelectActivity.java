package com.purdue.e_rccar;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class ParkingSelectActivity extends Activity {

    ////////////////////////////////////For Layout//////////////////////////////////////
    /**
     * ImageButton
     */
    ImageButton btn_rearparking;
    ImageButton btn_parallelparking;
    ////////////////////////////////////////////////////////////////////////////////////
    ModeSelectActivity msa = new ModeSelectActivity();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_parkingselect);

        btn_rearparking = (ImageButton) findViewById(R.id.btn_rearparking);
        btn_rearparking.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'p');
            }
        });

        btn_parallelparking = (ImageButton) findViewById(R.id.btn_parallelparking);
        btn_parallelparking.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'r');
            }
        });
    }

    // onDestroy() : 어플이 종료될때 호출 되는 함수.
    //               블루투스 연결이 필요하지 않는 경우 입출력 스트림 소켓을 닫아줌.
    @Override
    protected void onDestroy() {
        super.onDestroy();
        try {
        } catch (Exception e) {
        }
    }
}
