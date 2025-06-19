package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

@Keep
public class BootReceiver extends BroadcastReceiver {
    @Keep
    private static final String TAG = "BootReceiver";

    @Keep
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "Call onReceive");

        if (Intent.ACTION_BOOT_COMPLETED.equals(intent.getAction())) {
            boolean isAutoStartEnable = AutoStartManager.isAutoStart(context);

            Log.d(TAG, "Boot completed. Auto start: " + isAutoStartEnable);

            if (isAutoStartEnable) {
                Intent serviceIntent = new Intent(context, BootService.class);
                context.startForegroundService(serviceIntent);
                Log.d(TAG, "Started BootService");
            }
        }
    }
}
