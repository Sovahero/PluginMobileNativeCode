#pragma once

#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#include <iostream>
#include <string>

using namespace std;

class JavaConvert
{
public:
	//============== Функции для конвертирования в Java типы / Functions for converting to Java types ===================================

	// <FString>Arr to jobjectArray
	static jobjectArray ConvertToJStringArray(const TArray<FString>& stringArray);

	// <bool>Arr to jbooleanArray
	static jbooleanArray ConvertToJBooleanArray(const TArray<bool>& boolArray);

	// <int>Arr to jintArray
	static jintArray ConvertToJIntArray(const TArray<int>& intArray);

	// <unsigned char>Arr to jbyteArray
	static jbyteArray ConvertToJByteArray(const TArray<uint8>& byteArray);

	// <long>Arr to jlongArray
	static jlongArray ConvertToJLongArray(const TArray<long>& longArray);

	// jbyteArray to <unsigned char>Arr
	static TArray<uint8> ConvertToByteArray(jbyteArray javaArray);

	// jlongArray to <long>Arr
	static TArray<long> ConvertToLongArray(jlongArray javaArray);

	// jobjectArray to <FString>Arr
	static TArray<FString> ConvertToStringArray(jobjectArray javaStringArray);

	// FString to jstring
	static jstring GetJavaString(FString string);

	// string to jstring
	static jstring GetJavaString(string str);

	// const char* to jstring
	static jstring GetJavaString(const char* str);

	// jstring to FString
	static FString FromJavaFString(jstring javaString);

	// jstring to string
	static string FromJavaString(jstring javaString);
};
