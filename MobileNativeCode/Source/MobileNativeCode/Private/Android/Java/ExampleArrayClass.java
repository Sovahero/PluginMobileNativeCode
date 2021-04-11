package com.Plugins.MobileNativeCode;//Use only this package, do not change it!!!

import android.support.annotation.Keep;


@Keep
public class ExampleArrayClass {

	//Return String Array
	@Keep
	public static String[] TestArray(String[] text, boolean[] b, int[] i, long[] l, float[] f) {

		/*
		Some clever manipulations with arrays
		*/

		String[] ArrStr = { "string", "Array" };
		return ArrStr;
	}


}


