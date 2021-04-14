package com.chartoise.main.thread.util;

import android.os.Handler;
import android.os.Looper;

import androidx.annotation.Keep;

@Keep
public class MainThreadTask implements Runnable {
    private static final Handler sHandler = new Handler(Looper.getMainLooper());
    private final long mNativeContext;

    private static void createAndPost(long nativeContext) {
        sHandler.post(new MainThreadTask(nativeContext));
    }

    private MainThreadTask(long nativeContext) {
        mNativeContext = nativeContext;
    }

    @Override
    public void run() {
        run(mNativeContext);
    }

    private native void run(long nativeContext);
}
