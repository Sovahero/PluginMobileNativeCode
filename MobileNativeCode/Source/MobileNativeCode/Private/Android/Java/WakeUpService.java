package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import androidx.core.app.NotificationCompat;
import android.support.annotation.Keep;
import android.app.AlarmManager;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.IBinder;
import android.util.Log;

@Keep
public class WakeUpService extends Service {
    // Class tag for logging
    @Keep
    private static final String TAG = "WakeUpService";

    // AlarmManager instance for scheduling alarms
    @Keep
    private AlarmManager alarmManager;

    // WakeUpReceiver instance for listening DEVICE_IDLE_MODE_CHANGED
    @Keep
    private WakeUpReceiver wakeUpReceiver;
    
    // ShutdownReceiver instance for listening ACTION_SHUTDOWN and ACTION_SCREEN_OFF
    @Keep
    private ShutdownReceiver shutdownReceiver;

    // Static method to schedule next alarm; called from file WakeUpReceiver.java
    @Keep
    public static void onReceive(WakeUpService service, long triggerTime) {
        service.scheduleAlarm(triggerTime);
    }

    // Static method to stop WakeUpService; called from file ShutdownReceiver.java
    @Keep
    public static void checkStopWakeUpService(WakeUpService service) {
        if (!AppLifecycleObserver.getIsAppForeground()) {
            service.stopSelf();
            Log.d(TAG, "WakeUpService stopped because the app is in the background.");
        } else {
            Log.d(TAG, "WakeUpService is still running because the app is in the foreground.");
        }
    }

    // Start the service in the foreground with a notification
    @Keep
    private void startForegroundNotification() {
        Log.d(TAG, "Call startForegroundNotification");
        String channelId = "WakeUpChannel";
    
        // Create notification channel
        NotificationChannel channel = new NotificationChannel(
            channelId,
            "Wake Up Service Channel", // Channel name
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
        NotificationCompat.Builder builder = new NotificationCompat.Builder(getApplicationContext(), channelId)
                .setContentTitle(getText(android.R.string.dialog_alert_title)) // Placeholder title
                .setContentText(getText(android.R.string.dialog_alert_title))  // Placeholder content
                .setSmallIcon(android.R.drawable.ic_dialog_info)
                .setContentIntent(pendingIntent)
                .setLargeIcon(icon)
                .setPriority(NotificationCompat.PRIORITY_LOW);

        // Start foreground service to prevent being killed by the system
        startForeground(1, builder.build());
        Log.d(TAG, "Finish startForegroundNotification");
    }

    // Schedule an alarm clock with the specified trigger time
    @Keep
    private void scheduleAlarm(long triggerTime) {
        Log.d(TAG, "Call scheduleAlarm");
        // Create an intent to launch MainActivity when the alarm is triggered
        Intent intentMain = new Intent(getApplicationContext(), MainActivity.class);
        PendingIntent pendingIntentMain = PendingIntent.getActivity(
                getApplicationContext(), 0, intentMain, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);
        AlarmManager.AlarmClockInfo alarmInfo = new AlarmManager.AlarmClockInfo(triggerTime, pendingIntentMain);

        // Create an intent to restart this service when the alarm goes off
        Intent intentService = new Intent(getApplicationContext(), WakeUpService.class);
        PendingIntent pendingIntentService = PendingIntent.getService(
                getApplicationContext(), 1, intentService, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);

        alarmManager.setAlarmClock(alarmInfo, pendingIntentService);
        Log.d(TAG, "Finish scheduleAlarm");
    }

    // Static method to start the service
    @Keep
    public static void startService(Context context) {
        context.startService(new Intent(context, WakeUpService.class));
    }

    // Static method to stop the service
    @Keep
    public static void stopService(Context context) {
        context.stopService(new Intent(context, WakeUpService.class));
    }

    @Keep
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Keep
    @Override
    public void onCreate() {
        super.onCreate();
        Log.d(TAG, "Call onCreate");

        AppLifecycleObserver.register();

        // Initialize AlarmManager
        alarmManager = (AlarmManager) getApplicationContext().getSystemService(Context.ALARM_SERVICE);

        // Register a BroadcastReceiver to listen for DEVICE_IDLE_MODE_CHANGED action
        IntentFilter wakeUpReceiverFilter = new IntentFilter();
        wakeUpReceiverFilter.addAction("android.os.action.DEVICE_IDLE_MODE_CHANGED");

        // The WakeUpReceiver class (defined in WakeUpReceiver.java) will handle the broadcast
        wakeUpReceiver = new WakeUpReceiver(this);
        getApplicationContext().registerReceiver(wakeUpReceiver, wakeUpReceiverFilter);

        // Register a BroadcastReceiver to listen for ACTION_SHUTDOWN and ACTION_SCREEN_OFF action
        IntentFilter shutdownReceiverFilter = new IntentFilter();
        shutdownReceiverFilter.addAction(Intent.ACTION_SHUTDOWN); // Listen to Event Shutdown Device
        shutdownReceiverFilter.addAction(Intent.ACTION_SCREEN_OFF); //Listen to Event Turn off Screen

        // The ShutdownReceiver class (defined in ShutdownReceiver.java) will handle the broadcast
        shutdownReceiver = new ShutdownReceiver(this);
        getApplicationContext().registerReceiver(shutdownReceiver, shutdownReceiverFilter);

        // Start the foreground notification to ensure the service is not killed by the system
        startForegroundNotification();
        Log.d(TAG, "Finish onCreate()");
    }

    @Keep
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d(TAG, "Call onStartCommand");
        return super.onStartCommand(intent, flags, startId);
    }

    @Keep
    @Override
    public void onDestroy() {
        Log.d(TAG, "Call onDestroy");

        AppLifecycleObserver.unregister();

        try {
            // Unregister wakeUpReceiver
            try {
                if (wakeUpReceiver != null) {
                    getApplicationContext().unregisterReceiver(wakeUpReceiver);
                    wakeUpReceiver = null;
                    Log.d(TAG, "Unregister wakeUpReceiver");
                } else {
                    Log.d(TAG, "wakeUpReceiver null");
                }
            } catch (Exception e) {
                Log.e(TAG, "Error unregistering wakeUpReceiver", e);
            }

            // Unregister shutdownReceiver
            try {
                if (shutdownReceiver != null) {
                    getApplicationContext().unregisterReceiver(shutdownReceiver);
                    shutdownReceiver = null;
                    Log.d(TAG, "Unregister shutdownReceiver");
                } else {
                    Log.d(TAG, "shutdownReceiver null");
                }
            } catch (Exception e) {
                Log.e(TAG, "Error unregistering shutdownReceiver", e);
            }

            // Cancel alarm if set
            try {
                if (alarmManager != null) {
                    Intent intentService = new Intent(getApplicationContext(), WakeUpService.class);
                    PendingIntent pendingIntentService = PendingIntent.getService(
                            getApplicationContext(), 1, intentService, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);
                    alarmManager.cancel(pendingIntentService);
                    Log.d(TAG, "alarmManager cancelled");
                } else {
                    Log.d(TAG, "alarmManager null");
                }
            } catch (Exception e) {
                Log.e(TAG, "Error cancelling alarmManager", e);
            }
        } catch (Exception e) {
            Log.e(TAG, "Unexpected error in onDestroy", e);
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
