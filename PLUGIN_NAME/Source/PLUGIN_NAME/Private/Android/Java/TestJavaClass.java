package com.epicgames.ue4;
//Используйте только этот package, не изменяйте его!!!
//Use only this package, do not change it!!!

import android.app.Activity;
import android.support.annotation.Keep;
import android.widget.Toast;

import android.os.Build;
import android.os.Bundle;
import android.os.Environment;

import android.provider.Settings;
import android.content.Context;

import java.io.File;

@Keep
public class TestJavaClass {
	// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//----- Вызов Java кода синхроно / Calling Java code synchronously -------------------
	@Keep
	public static String HelloWorldOnAndroid(String text) {
		text += " on Android";
		return text;
	}
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// #~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// #~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@Keep 
	public static String[] TestArray(String[] text, boolean[] b, int[] i, long[] l, float[] f) { 
		String[] ArrStr = { "string", "Array" }; 
		return ArrStr;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// #~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//----- Path to "storage/emulated/0/Android/data/data/%APP_PACKAGE_NAME%/"------------------
	@Keep
	public static String GetExternalFilesDir(final Activity activity) {
		Context context = activity;
		File file = context.getExternalFilesDir(null);
		String PathStr = file.getPath();
		PathStr += "/";

		return PathStr;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}
