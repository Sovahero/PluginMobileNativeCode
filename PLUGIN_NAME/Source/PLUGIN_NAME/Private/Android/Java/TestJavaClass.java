package com.epicgames.ue4;
//Используйте только этот package, не изменяйте его!!!
//Use only this package, do not change it!!!

import android.app.Activity;
import android.support.annotation.Keep;
import android.widget.Toast;
import android.os.Build;
import android.provider.Settings;

@Keep
public class TestJavaClass {
	//---- Информация об устройстве / Device information ---------------------
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

	//---- Вызов всплывающего сообщения /Calling a pop-up message ----------------
	@Keep
	public static void showToast(final Activity activity, final String text, final int duration) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run()
			{
				Toast.makeText(activity, text, duration).show();
			}
		});
	}

	//----- Вызов Java кода синхроно / Calling Java code synchronously -------------------
	@Keep
	public static String HelloWorldOnAndroid(String text) {
		text += " on Android";
		return text;
	}

	//----- Вызов Java кода асинхроно и возвращение значения обратно в C++
	// Calling Java code asynchronously and returning the value back to C++ --------------
	@Keep
	public static native void CallBackCPP(String returnStr);

	@Keep
	public static void asyncHelloWorldOnAndroid(final Activity activity, final String text) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run()
			{
				CallBackCPP(text+" on Android");
			}
		});
	}
}
