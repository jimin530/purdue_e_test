package com.purdue.e_rccar;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.RotateAnimation;
import android.widget.ImageButton;
import android.widget.ImageView;

public class Mode1_1Activity extends Activity {

    ////////////////////////////////////For Layout//////////////////////////////////////
    /**
     * ImageButton
     */
    ImageButton btn_up;
    ImageButton btn_down;
    ImageButton btn_stop;
    ImageButton btn_step1;
    ImageButton btn_step2;
    ImageButton btn_step3;
    ImageButton btn_step4;
    ImageButton btn_step5;

    /**
     * ImageView
     */
    ImageView wheel;
    ////////////////////////////////////////////////////////////////////////////////////

    //wheel 회전
    private double mCurrAngle = 0, mPrevAngle = 0;
    private double mStart = 0, mSave = 0;

    ModeSelectActivity msa = new ModeSelectActivity();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mode1_1);

        msa.sendData(getApplicationContext(), 'd');

        btn_up = (ImageButton) findViewById(R.id.btn_up);
        btn_up.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'a');
            }
        });

        btn_down = (ImageButton) findViewById(R.id.btn_down);
        btn_down.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'b');
            }
        });

        btn_stop = (ImageButton) findViewById(R.id.btn_stop);
        btn_stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'c');
            }
        });

        btn_step1 = (ImageButton) findViewById(R.id.btn_step1);
        btn_step1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'd');
                btn_step1.setBackgroundResource(R.drawable.btnimg_step1_pressed);
                btn_step2.setBackgroundResource(R.drawable.btnimg_step2);
                btn_step3.setBackgroundResource(R.drawable.btnimg_step3);
                btn_step4.setBackgroundResource(R.drawable.btnimg_step4);
                btn_step5.setBackgroundResource(R.drawable.btnimg_step5);
            }
        });

        btn_step2 = (ImageButton) findViewById(R.id.btn_step2);
        btn_step2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'e');
                btn_step1.setBackgroundResource(R.drawable.btnimg_step1);
                btn_step2.setBackgroundResource(R.drawable.btnimg_step2_pressed);
                btn_step3.setBackgroundResource(R.drawable.btnimg_step3);
                btn_step4.setBackgroundResource(R.drawable.btnimg_step4);
                btn_step5.setBackgroundResource(R.drawable.btnimg_step5);
            }
        });

        btn_step3 = (ImageButton) findViewById(R.id.btn_step3);
        btn_step3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'f');
                btn_step1.setBackgroundResource(R.drawable.btnimg_step1);
                btn_step2.setBackgroundResource(R.drawable.btnimg_step2);
                btn_step3.setBackgroundResource(R.drawable.btnimg_step3_pressed);
                btn_step4.setBackgroundResource(R.drawable.btnimg_step4);
                btn_step5.setBackgroundResource(R.drawable.btnimg_step5);
            }
        });

        btn_step4 = (ImageButton) findViewById(R.id.btn_step4);
        btn_step4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'g');
                btn_step1.setBackgroundResource(R.drawable.btnimg_step1);
                btn_step2.setBackgroundResource(R.drawable.btnimg_step2);
                btn_step3.setBackgroundResource(R.drawable.btnimg_step3);
                btn_step4.setBackgroundResource(R.drawable.btnimg_step4_pressed);
                btn_step5.setBackgroundResource(R.drawable.btnimg_step5);
            }
        });

        btn_step5 = (ImageButton) findViewById(R.id.btn_step5);
        btn_step5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msa.sendData(getApplicationContext(), 'h');
                btn_step1.setBackgroundResource(R.drawable.btnimg_step1);
                btn_step2.setBackgroundResource(R.drawable.btnimg_step2);
                btn_step3.setBackgroundResource(R.drawable.btnimg_step3);
                btn_step4.setBackgroundResource(R.drawable.btnimg_step4);
                btn_step5.setBackgroundResource(R.drawable.btnimg_step5_pressed);
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
                        mStart = mSave = 0;
                        break;
                    }
                    case MotionEvent.ACTION_MOVE: {
                        mPrevAngle = mCurrAngle;
                        mCurrAngle = Math.toDegrees(Math.atan2(x - xc, yc - y));
                        diff = -mPrevAngle + mCurrAngle;

                        if (mStart <= 90 && mStart >= -90) {
                            animateWheel(mStart, mStart + diff, 0);
                            mStart += diff;
                        } else if (mStart > 90 && mStart < 180) {
                            mStart = 90;
                            diff = 0;
                            animateWheel(mStart, mStart, 0);
                        } else if (mStart < -90 && mStart > -180) {
                            mStart = -90;
                            diff = 0;
                            animateWheel(mStart, mStart, 0);
                        }

                        Log.i("현재 : ", setSignal(mStart) + "");
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
        msa.sendData(getApplicationContext(), 'c');
        btn_step1.setBackgroundResource(R.drawable.btnimg_step1);
        btn_step2.setBackgroundResource(R.drawable.btnimg_step2);
        btn_step3.setBackgroundResource(R.drawable.btnimg_step3);
        btn_step4.setBackgroundResource(R.drawable.btnimg_step4);
        btn_step5.setBackgroundResource(R.drawable.btnimg_step5);
        try {
        } catch (Exception e) {
        }
    }
}