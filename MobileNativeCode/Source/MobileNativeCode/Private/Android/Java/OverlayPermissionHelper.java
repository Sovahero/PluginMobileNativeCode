package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.provider.Settings;
import android.util.Log;

@Keep
public class OverlayPermissionHelper {
    @Keep
    private static final String TAG = "OverlayPermissionHelper";

    @Keep
    public static boolean isOverlayPermissionGranted(Activity activity) {
        return Settings.canDrawOverlays(activity.getApplicationContext());
    }

    @Keep
    public static void checkAndRequestOverlayPermission(Activity activity) {
        Log.d(TAG, "Call checkAndRequestOverlayPermission");

        if (!Settings.canDrawOverlays(activity.getApplicationContext())) {
            Log.d(TAG, "Requesting SYSTEM_ALERT_WINDOW permission in " + activity.getApplicationContext().getPackageName());
            Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + activity.getApplicationContext().getPackageName()));
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            activity.getApplicationContext().startActivity(intent);
        } else {
            Log.d(TAG, "App " + activity.getApplicationContext().getPackageName() + " had permission SYSTEM_ALERT_WINDOW. Don't request anymore");
        }
    }
}
