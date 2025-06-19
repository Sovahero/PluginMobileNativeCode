package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

@Keep
class ShutdownReceiver extends BroadcastReceiver {
    // Class tag for logging
    @Keep
    private static final String TAG = "ShutdownReceiver";

    @Keep
    final WakeUpService wakeUpService;

    @Keep
    ShutdownReceiver(WakeUpService paramWakeUpService) {
        this.wakeUpService = paramWakeUpService;
    }

    @Keep
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "Call onReceive");
        WakeUpService.checkStopWakeUpService(this.wakeUpService);
    }
}
