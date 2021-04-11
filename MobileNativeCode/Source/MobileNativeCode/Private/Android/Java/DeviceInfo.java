package com.Plugins.MobileNativeCode;


import android.app.Activity;
import android.os.Build;
import android.provider.Settings;
import androidx.annotation.Keep;
import android.content.Context;
import java.io.File;


//-- Device information
@Keep
public class DeviceInfo {

	//-- VersioN SDK
	@Keep
	public static int getSdkInt() {
		int SdkAndroid = Build.VERSION.SDK_INT;
		return SdkAndroid;
	}

	@Keep
	public static String getBrand() {
		return Build.BRAND;
	}

	@Keep
	public static String getModel() {
		return Build.MODEL;
	}

	@Keep
	public static String getAndroidId(Activity activity) {
		return Settings.Secure.getString(activity.getContentResolver(), Settings.Secure.ANDROID_ID);
	}

	//----- Path to "storage/emulated/0/Android/data/data/%APP_PACKAGE_NAME%/"------------------
	@Keep
	public static String GetExternalFilesDir(final Activity activity) {
		Context context = activity;
		File file = context.getExternalFilesDir(null);
		String PathStr = file.getPath();
		PathStr += "/";

		return PathStr;
	}

}





