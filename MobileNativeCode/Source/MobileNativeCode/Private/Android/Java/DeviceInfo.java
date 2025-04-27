package com.Plugins.MobileNativeCode;


import android.app.Activity;
import android.os.Build;
import androidx.annotation.Keep;
import android.content.Context;
import java.io.File;


//-- Device information
@Keep
public class DeviceInfo {

	//-- Init --
	@Keep
	public static int Initialization(){		
		return 1;
	}

	//---- VersioN SDK Phone ----------------
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