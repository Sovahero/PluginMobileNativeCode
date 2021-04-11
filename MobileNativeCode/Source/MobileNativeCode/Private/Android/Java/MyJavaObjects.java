package com.Plugins.MobileNativeCode;//Use only this package, do not change it!!!

import android.support.annotation.Keep;
import android.os.Bundle;

@Keep
public class MyJavaObjects {

	//----- Returns a new object of the type - Bundle -------------------
	@Keep
	public static Bundle getBundleJava(){
		return new Bundle();
	}

}

