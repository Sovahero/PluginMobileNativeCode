package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import android.app.Activity;
import android.util.Log;

@Keep
public class WakeUpManager {
    @Keep
    private static final String TAG = "WakeUpManager";

    @Keep
    public static void enableWakeUp(final Activity activity) {
        Log.d(TAG, "Enabling Wake Up");
        WakeUpService.startService(activity);
    }

    @Keep
    public static void disableWakeUp(final Activity activity) {
        Log.d(TAG, "Disabling Wake Up");
        WakeUpService.stopService(activity);
    }
}
