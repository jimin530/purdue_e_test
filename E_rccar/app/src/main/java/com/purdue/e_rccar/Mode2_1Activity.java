package com.purdue.e_rccar;

import android.app.Activity;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.RotateAnimation;
import android.widget.ImageButton;
import android.widget.ImageView;

import com.purdue.e_rccar.Gyro.GyroService;

public class Mode2_1Activity extends Activity {

    ////////////////////////////////////For Layout//////////////////////////////////////
    /**
     * ImageButton
     */
    ImageButton btn_gyrodrive;
    ImageView wheel;
    ////////////////////////////////////////////////////////////////////////////////////

    //wheel 회전
    private double mCurrAngle = 0, mPrevAngle = 0;
    private double mStart = 0,  mSave = 0;

    //자이로 플래그
    boolean gyro_start = false;

    //자이로 이미지 drawable
    Drawable btn_gyrodrive_draw;

    ModeSelectActivity msa = new ModeSelectActivity();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mode2_1);

        btn_gyrodrive = (ImageButton) findViewById(R.id.btn_gyrodrive);
        btn_gyrodrive.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (gyro_start) { // 주행 -> 멈춤
                    btn_gyrodrive_draw = getResources().getDrawable(R.drawable.btnimg_dirve_off);
                    btn_gyrodrive.setBackground(btn_gyrodrive_draw);
                    gyro_start = false;
                    stopService(new Intent(getApplicationContext(), GyroService.class));
                } else if (!gyro_start) { // 멈춤 -> 주행
                    btn_gyrodrive_draw = getResources().getDrawable(R.drawable.btnimg_drive_on);
                    btn_gyrodrive.setBackground(btn_gyrodrive_draw);
                    gyro_start = true;
                    startService(new Intent(getApplicationContext(), GyroService.class));
                }
            }
        });

        wheel = (ImageView) findViewById(R.id.wheel);
        wheel.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View v, MotionEvent event) {
                final float xc = wheel.getWidth() / 2;//450 x 450
                final float yc = wheel.getHeight() / 2;

                final float x = event.getX();
                final float y = event.getY();

                double diff;

                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN: {
                        mCurrAngle = Math.toDegrees(Math.atan2(x - xc, yc - y));
                        mStart=mSave = 0;
                        break;
                    }
                    case MotionEvent.ACTION_MOVE: {
                        mPrevAngle = mCurrAngle;
                        mCurrAngle = Math.toDegrees(Math.atan2(x - xc, yc - y));
                        diff = -mPrevAngle + mCurrAngle;

                        if (mStart <= 90 && mStart >= -90){
                            animateWheel(mStart,mStart+diff,0);
                            mStart += diff;
                        }
                        else if (mStart > 90 && mStart < 180){
                            mStart = 90;diff=0;
                            animateWheel(mStart,mStart,0);
                        }
                        else if (mStart < -90 && mStart > -180){
                            mStart = -90;diff=0;
                            animateWheel(mStart,mStart,0);
                        }

                        Log.i("현재 : ",setSignal(mStart)+"");
                        if (setSignal(mStart).equals("middle")) {
                            msa.sendData(getApplicationContext(), 'i');
                        } else if (setSignal(mStart).equals("left1")) {
                            msa.sendData(getApplicationContext(), 'j');
                        } else if (setSignal(mStart).equals("left2")) {
                            msa.sendData(getApplicationContext(), 'k');
                        } else if (setSignal(mStart).equals("left3")) {
                            msa.sendData(getApplicationContext(), 'l');
                        } else if (setSignal(mStart).equals("right1")) {
                            msa.sendData(getApplicationContext(), 'm');
                        } else if (setSignal(mStart).equals("right2")) {
                            msa.sendData(getApplicationContext(), 'n');
                        } else if (setSignal(mStart).equals("right3")) {
                            msa.sendData(getApplicationContext(), 'o');
                        }

                        break;
                    }
                    case MotionEvent.ACTION_UP: {
                        animateWheel(mCurrAngle, 0, 0);
                        break;
                    }
                }
                return true;
            }
        });
    }

    private void animateWheel(double fromDegrees, double toDegrees, long durationMillis) {
        final RotateAnimation rotate = new RotateAnimation((float) fromDegrees, (float) toDegrees, RotateAnimation.RELATIVE_TO_SELF, 0.5f, RotateAnimation.RELATIVE_TO_SELF, 0.5f);
        rotate.setDuration(durationMillis);
        rotate.setFillEnabled(true);
        rotate.setFillAfter(true);
        wheel.startAnimation(rotate);
    }

    private String setSignal(double finalAngle) {
        String ret = null;
        finalAngle = finalAngle / 30;

        if (finalAngle > 0 && finalAngle <= 1)
            ret = "middle";
        else if (finalAngle > 1 && finalAngle <= 2)
            ret = "right1";
        else if (finalAngle > 2 && finalAngle < 3)
            ret = "right2";
        else if (finalAngle >= -1 && finalAngle < 0)
            ret = "middle";
        else if (finalAngle >= -2 && finalAngle < -1)
            ret = "left1";
        else if (finalAngle >= -3 && finalAngle < -2)
            ret = "left2";
        else if (finalAngle < -3)
            ret = "left3";
        else if (finalAngle >= 3)
            ret = "right3";
        return ret;
    }

    // onDestroy() : 어플이 종료될때 호출 되는 함수.
    //               블루투스 연결이 필요하지 않는 경우 입출력 스트림 소켓을 닫아줌.
    @Override
    protected void onDestroy() {
        super.onDestroy();
        btn_gyrodrive_draw = getResources().getDrawable(R.drawable.btnimg_dirve_off);
        btn_gyrodrive.setBackground(btn_gyrodrive_draw);
        stopService(new Intent(getApplicationContext(), GyroService.class));
        try {
        } catch (Exception e) {
        }
    }
}
