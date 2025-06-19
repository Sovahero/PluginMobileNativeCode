package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

@Keep
public class ScreenStateReceiver extends BroadcastReceiver {
    @Keep
    private static final String TAG = "ScreenStateReceiver";

    @Keep
    final BootService bootService;

    //Run this receiver only one time
    @Keep
    public boolean isRun = false;

    @Keep
    ScreenStateReceiver(BootService paramBootService) {
        this.bootService = paramBootService;
    }

    @Keep
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "Call onReceive");

        if (intent == null || !intent.getAction().equals("com.oculus.intent.action.MOUNT_STATE_CHANGED")) {
            Log.d(TAG, "Not com.oculus.intent.action.MOUNT_STATE_CHANGED");
            return;
        }

        boolean isMounted = intent.getBooleanExtra("state", false);
        Log.d(TAG, "Mount state changed: " + isMounted);

        if (isMounted && !isRun) {
            if (BootService.appIsRun) {
                isRun = true;
                BootService.resetSystemMenu(bootService);
            } else {
                isRun = true;
                Log.d(TAG, "App is not run. Don't use " + TAG + " anymore");
            }
            
        }
    }   
}
