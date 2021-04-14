package com.chartoise.main.thread.util;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private Handler mHandler;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("main-thread-utils");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        HandlerThread handlerThread = new HandlerThread("test");
        handlerThread.start();
        mHandler = new Handler(handlerThread.getLooper());

        findViewById(R.id.button_run_tests).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        runTests();
                    }
                });
            }
        });
    }

    private native void runTests();
}
