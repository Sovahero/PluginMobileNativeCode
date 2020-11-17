#pragma once

#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "JavaConvert.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class AndroidUtils
{
public:	
	//------------ Convert ---------------------------------------------------	
	template <typename anyType>
	static const anyType& convertArg(const anyType& value);
	static jstring convertArg(const char* str);
	static jstring convertArg(string str);
	static jstring convertArg(FString str);
	static jobjectArray convertArg(TArray<FString> stringArray);
	static jobjectArray convertArg(TArray<const char*> stringArray);
	static jobjectArray convertArg(TArray<string> stringArray);
	static jbooleanArray convertArg(TArray<bool> boolArray);
	static jintArray convertArg(TArray<int> intArray);
	static jbyteArray convertArg(TArray<uint8> byteArray);
	static jlongArray convertArg(TArray<long> longArray);
	static jfloatArray convertArg(TArray<float> floatArray);

	//================Override Tempalte===========================
	static string GetTypeName(void);
	static string GetTypeName(bool b);
	static string GetTypeName(unsigned char uc);
	static string GetTypeName(char c);
	static string GetTypeName(short s);
	static string GetTypeName(int i);
	static string GetTypeName(long l);
	static string GetTypeName(float f);
	static string GetTypeName(double d);
	static string GetTypeName(const char* str);
	static string GetTypeName(string str);
	static string GetTypeName(FString str);
	static string GetTypeName(jstring str);
	static string GetTypeName(jobject jo);
	static string GetTypeName(jobjectArray joa);
	//----array
	template<typename anyType>
	static string GetTypeName(TArray<anyType> anyArr);
	template<typename anyType>
	static string GetTypeName(std::vector<anyType> anyArr);
	//-----------------------------------------------------------------------------------------------	
	static void GetType(string&);

	template <typename T, typename... Args>
	static void GetType(string& signatureString, T Tvalue, Args... args);

	//==============Call Target Jni===================================
	static void CallJniVoidMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	static FString CallJniStringMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	static bool CallJniBoolMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	static int CallJniIntMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	static long CallJniLongMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	static jobject CallJniObjectMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	static jobjectArray CallJniObjectArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	static jfloatArray CallJniFloatArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	static jintArray CallJniIntArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);

	//-----------------------------------------------------------------------------------------------	
	// void
	template <typename... Args>
	static void CallVoidJni(const char* ClassName, const char* MethodName, const char* MethodSignature, Args... args);

	// FString
	template <typename... Args>
	static FString CallJNI(FString str, const char* ClassName, const char* MethodName, const char* MethodSignature, Args... args);

	// string
	template <typename... Args>
	static string CallJNI(string str, const char* ClassName, const char* MethodName, const char* MethodSignature, Args... args);

	// bool
	template <typename... Args>
	static bool CallJNI(bool b, const char* ClassName, const char* MethodName, const char* MethodSignature, Args... args);

	// int
	template <typename... Args>
	static int CallJNI(int i, const char* ClassName, const char* MethodName, const char* MethodSignature, Args... args);

	// long
	template <typename... Args>
	static long CallJNI(long l, const char* ClassName, const char* MethodName, const char* MethodSignature, Args... args);

	// jobject
	template <typename... Args>
	static jobject CallJNI(jobject jo, const char* ClassName, const char* MethodName, const char* MethodSignature, Args... args);

	// TArray<FString>
	template<typename ...Args>
	static TArray<FString> CallJNI(TArray<FString> strArr, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args);

	// TArray<float>
	template<typename ...Args>
	static TArray<float> CallJNI(TArray<float> strArr, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args);

	// TArray<int>
	template<typename ...Args>
	static TArray<int> CallJNI(TArray<int> iArr, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args);





	//============Вызов нативного кода Android из C++ / Calling native Android code from C++===============
	/**
	* Вызов собственного кода Java с возвращаемым значением / Calling native Java code with the return value
	*
	* @param ClassName - package(используется com/epicgames/ue4) и имя вашего Java класса / package (used by com/epicgames/ue4) and the name of your Java class.
	* @param FunctionName - Имя вашей Java функции / Name of your Java function.
	* @param isActivity - Определяет нужно ли передавать Activity UE4 в Java / Determines whether to pass Activity UE4 to Java.
	* @param args... -
	* Список ваших параметров в Java функции(если тип переменной в Java коде специфичный например jobject,
	* его следует перед вызовом функции переконвертировать) /
	* A list of your parameters in the Java function(if the variable type in the Java code is specific, such as jobject, it should be converted before calling the function).
	*/
	template <typename MethodType, typename... Args>
	static MethodType CallNativeAndroid(const char* ClassName, const char* FunctionName, bool isActivity, Args... args);

	/**
	* Вызов собственного кода Java без возвращаемого значения / Calling native Java code without a return value
	*
	* @param ClassName - package(используется com/epicgames/ue4) и имя вашего Java класса / package (used by com/epicgames/ue4) and the name of your Java class.
	* @param FunctionName - Имя вашей Java функции / Name of your Java function.
	* @param isActivity - Определяет нужно ли передавать Activity UE4 в Java / Determines whether to pass Activity UE4 to Java.
	* @param args... -
	* Список ваших параметров в Java функции(если тип переменной в Java коде специфичный например jobject,
	* его следует перед вызовом функции переконвертировать) /
	* A list of your parameters in the Java function(if the variable type in the Java code is specific, such as jobject, it should be converted before calling the function).
	*/
	template <typename... Args>
	static void CallNativeAndroidVoid(const char* ClassName, const char* FunctionName, bool isActivity, Args... args);
	//========================================================
};
