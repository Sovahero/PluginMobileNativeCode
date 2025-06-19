package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.util.Log;

@Keep
public class AutoStartManager {
    @Keep
    private static final String TAG = "AutoStartManager";

    @Keep
    private static final String PREFS_NAME = "AutoStartPrefs";

    @Keep
    private static final String KEY_AUTO_START = "AUTO_START";

    @Keep
    public static void enableAutoStart(Activity activity) {
        setAutoStart(activity.getApplicationContext(), true);
    }

    @Keep
    public static void disableAutoStart(Activity activity) {
        setAutoStart(activity.getApplicationContext(), false);
    }

    @Keep
    public static boolean isAutoStartEnable(Activity activity) {
        return isAutoStart(activity.getApplicationContext());
    }

    @Keep
    public static boolean isAutoStart(Context context) {
        SharedPreferences prefs = context.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        return prefs.getBoolean(KEY_AUTO_START, false);
    }

    @Keep
    private static void setAutoStart(Context context, boolean enabled) {
        SharedPreferences prefs = context.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        prefs.edit().putBoolean(KEY_AUTO_START, enabled).apply();
        Log.d(TAG, "AutoStart set to: " + enabled);
    }

    // public static void lockTask(Activity activity) { ... }
    // public static void hideSystemUI(Activity activity) { ... }
    // public static void scheduleReboot(...) { ... }
}
