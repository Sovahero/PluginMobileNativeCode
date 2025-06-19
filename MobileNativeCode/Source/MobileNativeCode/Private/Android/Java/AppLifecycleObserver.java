package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import androidx.lifecycle.Lifecycle;
import androidx.lifecycle.LifecycleObserver;
import androidx.lifecycle.OnLifecycleEvent;
import androidx.lifecycle.ProcessLifecycleOwner;
import android.util.Log;

@Keep
public class AppLifecycleObserver implements LifecycleObserver {
    // Class tag for logging
    @Keep
    private static final String TAG = "AppLifecycleObserver";

    @Keep
    private static boolean isAppForeground = false;

    @Keep
    private static AppLifecycleObserver instance;

    @Keep
    AppLifecycleObserver() {
        Log.d(TAG, "Init AppLifecycleObserver");
    }

    // First launch application
    @OnLifecycleEvent(Lifecycle.Event.ON_CREATE)
    public void onCreateEvent() {
        Log.d(TAG, "Call onCreateEvent");
    }

    // The application is opened or returned from the background
    @Keep
    @OnLifecycleEvent(Lifecycle.Event.ON_START)
    public void onStartEvent() {
        Log.d(TAG, "Call onStartEvent");
        isAppForeground = true;
    }

    // The application is no longer visible on the screen (but still running in the background)
    @Keep
    @OnLifecycleEvent(Lifecycle.Event.ON_PAUSE)
    public void onPauseEvent() {
        Log.d(TAG, "Call onPauseEvent");
    }
    
    // The application
    @Keep
    @OnLifecycleEvent(Lifecycle.Event.ON_RESUME)
    public void onResumeEvent() {
        Log.d(TAG, "Call onResumeEvent");
    }

    // The application is no longer visible on the screen (but still running in the background)
    @Keep
    @OnLifecycleEvent(Lifecycle.Event.ON_STOP)
    public void onStopEvent() {
        Log.d(TAG, "Call onStopEvent");
        isAppForeground = false;
    }

    // The application is destroyed
    @OnLifecycleEvent(Lifecycle.Event.ON_DESTROY)
    public void onDestroyEvent() {
        Log.d(TAG, "Call onDestroyEvent");
    }

    @Keep
    public static boolean getIsAppForeground() {
        return isAppForeground;
    }

    @Keep
    public static void register() {
        if (instance == null) {
            instance = new AppLifecycleObserver();
            ProcessLifecycleOwner.get().getLifecycle().addObserver(instance);
            Log.d(TAG, "AppLifecycleObserver registered.");
        } else {
            Log.d(TAG, "AppLifecycleObserver has been registered, don't need register anymore.");
        }
    }

    @Keep
    public static void unregister() {
        if (instance != null) {
            ProcessLifecycleOwner.get().getLifecycle().removeObserver(instance);
            instance = null;
            Log.d(TAG, "AppLifecycleObserver unregistered.");
        } else {
            Log.d(TAG, "AppLifecycleObserver has been null, don't need unregister anymore.");
        }
    }
}
