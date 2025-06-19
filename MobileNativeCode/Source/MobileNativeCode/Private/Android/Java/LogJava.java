package com.Plugins.MobileNativeCode;

import androidx.annotation.Keep;
import android.util.Log;

@Keep
public class LogJava {
    @Keep
    public static void logJava(String tag, String inString) {
        Log.d(tag, inString);
    }
}
