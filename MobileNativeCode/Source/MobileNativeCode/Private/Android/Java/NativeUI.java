package com.Plugins.MobileNativeCode;

import android.app.Activity;
import android.support.annotation.Keep;
import android.widget.Toast;


@Keep
public class NativeUI {

	//---- Calling a pop-up message ----------------
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
	
}
