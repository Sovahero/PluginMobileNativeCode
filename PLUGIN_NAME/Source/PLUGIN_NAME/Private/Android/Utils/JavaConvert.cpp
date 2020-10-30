#include "JavaConvert.h"

//==============Java Convert===================================

// <FString>Arr to jobjectArray
jobjectArray JavaConvert::ConvertToJStringArray(const TArray<FString>& stringArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobjectArray javaStringArray = (jobjectArray)Env->NewObjectArray(stringArray.Num(), FJavaWrapper::JavaStringClass, nullptr);
	for (int i = 0; i < stringArray.Num(); i++) {
		Env->SetObjectArrayElement(javaStringArray, i, JavaConvert::GetJavaString(stringArray[i]));
	}
	return javaStringArray;
}

// <bool>Arr to jbooleanArray
jbooleanArray JavaConvert::ConvertToJBooleanArray(const TArray<bool>& boolArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jbooleanArray javaBooleanArray = (jbooleanArray)Env->NewBooleanArray(boolArray.Num());
	jboolean* javaBooleanArrayPtr = Env->GetBooleanArrayElements(javaBooleanArray, 0);
	for (int i = 0; i < boolArray.Num(); i++) {
		javaBooleanArrayPtr[i] = boolArray[i];
	}
	return javaBooleanArray;
}

// <int>Arr to jintArray
jintArray JavaConvert::ConvertToJIntArray(const TArray<int>& intArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jintArray javaIntArray = (jintArray)Env->NewIntArray(intArray.Num());
	jint* javaIntArrayPtr = (jint*)malloc(intArray.Num() * sizeof(jint));
	for (int i = 0; i < intArray.Num(); i++) {
		javaIntArrayPtr[i] = (jint)intArray[i];
	}
	Env->SetIntArrayRegion(javaIntArray, 0, intArray.Num(), javaIntArrayPtr);
	free(javaIntArrayPtr);
	return javaIntArray;
}

// <unsigned char>Arr to jbyteArray
jbyteArray JavaConvert::ConvertToJByteArray(const TArray<uint8>& byteArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jbyteArray javaByteArray = (jbyteArray)Env->NewByteArray(byteArray.Num());
	jbyte* javaByteArrayPtr = (jbyte*)malloc(byteArray.Num() * sizeof(jbyte));
	for (int i = 0; i < byteArray.Num(); i++) {
		javaByteArrayPtr[i] = byteArray[i];
	}
	Env->SetByteArrayRegion(javaByteArray, 0, byteArray.Num(), javaByteArrayPtr);
	free(javaByteArrayPtr);
	return javaByteArray;
}

// <long>Arr to jlongArray
jlongArray JavaConvert::ConvertToJLongArray(const TArray<long>& longArray)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jlongArray javaLongArray = (jlongArray)Env->NewLongArray(longArray.Num());
	jlong* javaLongArrayPtr = (jlong*)malloc(longArray.Num() * sizeof(jlong));
	for (int i = 0; i < longArray.Num(); i++) {
		javaLongArrayPtr[i] = longArray[i];
	}
	Env->SetLongArrayRegion(javaLongArray, 0, longArray.Num(), javaLongArrayPtr);
	free(javaLongArrayPtr);
	return javaLongArray;
}

// jbyteArray to <unsigned char>Arr
TArray<uint8> JavaConvert::ConvertToByteArray(jbyteArray javaArray)
{
	TArray<uint8> byteArray;
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jbyte* javaByte = Env->GetByteArrayElements(javaArray, 0);
	int length = Env->GetArrayLength(javaArray);
	for (int i = 0; i < length; i++) {
		byteArray.Add(javaByte[i]);
	}
	return byteArray;
}

// jlongArray to <long>Arr
TArray<long> JavaConvert::ConvertToLongArray(jlongArray javaArray)
{
	TArray<long> longArray;
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jlong* javaLong = Env->GetLongArrayElements(javaArray, 0);
	int length = Env->GetArrayLength(javaArray);
	for (int i = 0; i < length; i++)
	{
		longArray.Add((long)javaLong[i]);
	}
	return longArray;
}

// jobjectArray to <FString>Arr
TArray<FString> JavaConvert::ConvertToStringArray(jobjectArray javaStringArray)
{
	TArray<FString> stringArray;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	int length = Env->GetArrayLength(javaStringArray);

	for (int i = 0; i < length; i++)
	{
		jstring javaString = static_cast<jstring>(Env->GetObjectArrayElement(javaStringArray, i));

		stringArray.Add(JavaConvert::FromJavaFString(javaString));
	}

	return stringArray;
}

// FString to jstring
jstring JavaConvert::GetJavaString(FString string)
{
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jstring local = JEnv->NewStringUTF(TCHAR_TO_UTF8(*string));
	jstring result = (jstring)JEnv->NewGlobalRef(local);
	JEnv->DeleteLocalRef(local);
	return result;
}

// string to jstring
jstring JavaConvert::GetJavaString(string str)
{
	FString string = str.c_str();
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jstring local = JEnv->NewStringUTF(TCHAR_TO_UTF8(*string));
	jstring result = (jstring)JEnv->NewGlobalRef(local);
	JEnv->DeleteLocalRef(local);
	return result;
}

// const char* to jstring
jstring JavaConvert::GetJavaString(const char* str)
{
	string sstr = str;
	FString string = sstr.c_str();
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jstring local = JEnv->NewStringUTF(TCHAR_TO_UTF8(*string));
	jstring result = (jstring)JEnv->NewGlobalRef(local);
	JEnv->DeleteLocalRef(local);
	return result;
}

// jstring to FString
FString JavaConvert::FromJavaFString(jstring javaString)
{
	JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
	const char* UTFString = Env->GetStringUTFChars(javaString, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(javaString, UTFString);
	Env->DeleteLocalRef(javaString);

	return Result;
}

// jstring to string
string JavaConvert::FromJavaString(jstring javaString)
{
	JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
	const char* UTFString = Env->GetStringUTFChars(javaString, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(javaString, UTFString);
	Env->DeleteLocalRef(javaString);

	return string(TCHAR_TO_UTF8(*Result));
}

