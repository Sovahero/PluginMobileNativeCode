package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

@Keep
class WakeUpReceiver extends BroadcastReceiver {
    // Class tag for logging
    @Keep
    private static final String TAG = "WakeUpReceiver";

    @Keep
    final WakeUpService wakeUpService;

    @Keep
    WakeUpReceiver(WakeUpService paramWakeUpService) {
        this.wakeUpService = paramWakeUpService;
    }

    @Keep
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "Call onReceive");
        WakeUpService.onReceive(this.wakeUpService, System.currentTimeMillis() + 1000L);
    }
}
