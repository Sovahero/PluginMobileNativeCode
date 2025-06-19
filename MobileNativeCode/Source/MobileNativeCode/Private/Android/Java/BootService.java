package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import androidx.core.app.NotificationCompat;
import android.app.Service;
import android.app.PendingIntent;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.IBinder;
import android.util.Log;

@Keep
public class BootService extends Service {
    @Keep
    private static final String TAG = "BootService";

    @Keep
    private static final String CHANNEL_ID = "BootChannel";

    @Keep
    public static boolean appIsRun = false;

    @Keep
    private ScreenStateReceiver screenStateReceiver;

    @Keep
    public static void minimizeApp(Context context) {
        Intent intent = new Intent(Intent.ACTION_MAIN);
        intent.addCategory(Intent.CATEGORY_HOME);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(intent);
    }

    @Keep
    public static void restoreApp(Context context) {
        Intent launchIntent = context.getPackageManager().getLaunchIntentForPackage(context.getPackageName());
        if (launchIntent != null) {
            launchIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(launchIntent);
        }
    }

    // Static method to call resend Oculus Menu Intent
    @Keep
    public static void resetSystemMenu(BootService service) {
        Log.d(TAG, "Call resetSystemMenu");
        new Thread(() -> {
            Log.d(TAG, "Start run minimizeApp");
            minimizeApp(service);
            Log.d(TAG, "Finish run minimizeApp");

            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            Log.d(TAG, "Start run restoreApp");
            restoreApp(service);
            Log.d(TAG, "Finish run restoreApp");

            service.stopSelf();
        }).start();
    }

    // Start the service in the foreground with a notification
    @Keep
    private void startForegroundNotification() {
        Log.d(TAG, "Call startForegroundNotification");
    
        // Create notification channel
        NotificationChannel channel = new NotificationChannel(
            CHANNEL_ID,
            "Boot Service Channel", // Channel name
            NotificationManager.IMPORTANCE_LOW // Importance level
        );
        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        if (notificationManager != null) {
            notificationManager.createNotificationChannel(channel);
        }

        // Create a PendingIntent to launch MainActivity when notification is tapped
        PendingIntent pendingIntent = PendingIntent.getActivity(
                this, 0, new Intent(this, MainActivity.class), PendingIntent.FLAG_IMMUTABLE);

        // Decode a bitmap from resource (replace with your own resource ID as needed)
        Bitmap icon = BitmapFactory.decodeResource(getResources(), android.R.drawable.ic_dialog_info);

        // Build the notification using NotificationCompat.Builder
        NotificationCompat.Builder builder = new NotificationCompat.Builder(getApplicationContext(), CHANNEL_ID)
                .setContentTitle(getText(android.R.string.dialog_alert_title)) // Placeholder title
                .setContentText(getText(android.R.string.dialog_alert_title))  // Placeholder content
                .setSmallIcon(android.R.drawable.ic_dialog_info)
                .setContentIntent(pendingIntent)
                .setLargeIcon(icon)
                .setPriority(NotificationCompat.PRIORITY_LOW);

        // Start foreground service to prevent being killed by the system
        startForeground(1, builder.build());
        Log.d(TAG, "Finish startForegroundNotification()");
    }

    @Keep
    @Override
    public void onCreate() {
        super.onCreate();

        Log.d(TAG, "Call onCreate");

        IntentFilter screenStateReceiverFilter = new IntentFilter();
        screenStateReceiverFilter.addAction("com.oculus.intent.action.MOUNT_STATE_CHANGED");

        // The ScreenStateReceiver class (defined in ScreenStateReceiver.java) will handle the broadcast
        screenStateReceiver = new ScreenStateReceiver(this);
        getApplicationContext().registerReceiver(screenStateReceiver, screenStateReceiverFilter);

        // Start the foreground notification to ensure the service is not killed by the system
        startForegroundNotification();
    }

    @Keep
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d(TAG, "Call onStartCommand");

        new Thread(() -> {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            Log.d(TAG, "Start to launch app " + getApplicationContext().getPackageName());

            Intent launchIntent = getPackageManager().getLaunchIntentForPackage(getApplicationContext().getPackageName());
            if (launchIntent != null) {
                launchIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(launchIntent);
                BootService.appIsRun = true;
                Log.d(TAG, "App " + getApplicationContext().getPackageName() + " launched successfully");
                if (screenStateReceiver.isRun) {
                    stopSelf();
                }
            } else {
                Log.d(TAG, "Launch intent is null");
            }

        }).start();

        return START_STICKY;
    }

    @Keep
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Keep
    @Override
    public void onDestroy() {
        Log.d(TAG, "Call onDestroy");

        // Unregister screenStateReceiver
        try {
            if (screenStateReceiver != null) {
                getApplicationContext().unregisterReceiver(screenStateReceiver);
                screenStateReceiver = null;
                Log.d(TAG, "Unregister screenStateReceiver");
            } else {
                Log.d(TAG, "screenStateReceiver null");
            }
        } catch (Exception e) {
            Log.e(TAG, "Error unregistering screenStateReceiver", e);
        }

        // Stop the foreground service
        try {
            stopForeground(true);
            Log.d(TAG, "Stopped foreground service");
        } catch (Exception e) {
            Log.e(TAG, "Error stopping foreground service", e);
        }

        super.onDestroy();
        Log.d(TAG, "Finish onDestroy");
    }
}
