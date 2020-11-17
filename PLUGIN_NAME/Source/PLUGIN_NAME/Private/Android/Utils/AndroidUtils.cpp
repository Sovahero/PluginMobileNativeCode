#include "AndroidUtils.h"

//=============== Override Convert===========================
template<typename anyType>
const anyType& AndroidUtils::convertArg(const anyType& value) {
	return value;
}
jstring AndroidUtils::convertArg(const char* str)
{
	return JavaConvert::GetJavaString(str);
}
jstring AndroidUtils::convertArg(string str)
{
	return JavaConvert::GetJavaString(str);
}
jstring AndroidUtils::convertArg(FString str)
{
	return JavaConvert::GetJavaString(str);
}
//---array
jobjectArray AndroidUtils::convertArg(TArray<const char*> stringArray)
{
	TArray<FString> tmpFString;
	for (auto tmpCellStringArray : stringArray) {
		string tmpString = tmpCellStringArray;
		tmpFString.Add(tmpString.c_str());
	}
	return JavaConvert::ConvertToJStringArray(tmpFString);
}
jobjectArray AndroidUtils::convertArg(TArray<string> stringArray)
{
	TArray<FString> tmpFString;
	for (auto tmpCellStringArray : stringArray)
		tmpFString.Add(tmpCellStringArray.c_str());

	return JavaConvert::ConvertToJStringArray(tmpFString);
}
jobjectArray AndroidUtils::convertArg(TArray<FString> stringArray)
{
	return JavaConvert::ConvertToJStringArray(stringArray);
}
jbooleanArray AndroidUtils::convertArg(TArray<bool> boolArray)
{
	return JavaConvert::ConvertToJBooleanArray(boolArray);
}
jintArray AndroidUtils::convertArg(TArray<int> intArray)
{
	return JavaConvert::ConvertToJIntArray(intArray);
}
jbyteArray AndroidUtils::convertArg(TArray<uint8> byteArray)
{
	return JavaConvert::ConvertToJByteArray(byteArray);
}
jlongArray AndroidUtils::convertArg(TArray<long> longArray)
{
	return JavaConvert::ConvertToJLongArray(longArray);
}
jfloatArray AndroidUtils::convertArg(TArray<float> floatArray)
{
	return JavaConvert::ConvertToJFloatArray(floatArray);
}


//=============== Override Tempalte===========================
string AndroidUtils::GetTypeName(void)
{
	return "V";
}
string AndroidUtils::GetTypeName(bool b)
{
	return "Z";
}
string AndroidUtils::GetTypeName(unsigned char uc)
{
	return "B";
}
string AndroidUtils::GetTypeName(char c)
{
	return "C";
}
string AndroidUtils::GetTypeName(short s)
{
	return "S";
}
string AndroidUtils::GetTypeName(int i)
{
	return "I";
}
string AndroidUtils::GetTypeName(long l)
{
	return "J";
}
string AndroidUtils::GetTypeName(float f)
{
	return "F";
}
string AndroidUtils::GetTypeName(double d)
{
	return "D";
}
string AndroidUtils::GetTypeName(const char* str)
{
	return "Ljava/lang/String;";
}
string AndroidUtils::GetTypeName(string str)
{
	return "Ljava/lang/String;";
}
string AndroidUtils::GetTypeName(FString str)
{
	return "Ljava/lang/String;";
}
string AndroidUtils::GetTypeName(jstring str)
{
	return "Ljava/lang/String;";
}
string AndroidUtils::GetTypeName(jobject jo)
{
	return "Ljava/lang/Object;";
}
//----array
string AndroidUtils::GetTypeName(jobjectArray joa)
{
	return "[Ljava/lang/Object;";
}
template<typename anyType>
string AndroidUtils::GetTypeName(TArray<anyType> anyArr) {
	anyType SymbolType{};
	return string("[" + GetTypeName(SymbolType));
}
template<typename anyType>
string AndroidUtils::GetTypeName(std::vector<anyType> anyArr) {
	anyType SymbolType{};
	return string("[" + GetTypeName(SymbolType));
}

//=============== Recursion Method for Variadic Template===========================
// ------------ GetType
template<typename anyType, typename ...Args>
void AndroidUtils::GetType(string& signatureString, anyType value, Args ...args)
{
	signatureString += GetTypeName(value);
	GetType(signatureString, args...);
}
// ------------ GetType
void AndroidUtils::GetType(string&) {   }


//=============== Call Target Jni ========================================
void AndroidUtils::CallJniVoidMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniVoidMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	Env->CallStaticVoidMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);
}

FString AndroidUtils::CallJniStringMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniStringMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	jstring Return = static_cast<jstring>(Env->CallStaticObjectMethodV(Class, Method, Args));
	va_end(Args);

	const char* UTFString = Env->GetStringUTFChars(Return, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(Return, UTFString);
	Env->DeleteLocalRef(Class);

	return Result;
}
bool AndroidUtils::CallJniBoolMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniBoolMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	bool Result = Env->CallStaticBooleanMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}
int AndroidUtils::CallJniIntMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniIntMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	int Result = Env->CallStaticIntMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}
long AndroidUtils::CallJniLongMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniLongMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	long Result = Env->CallStaticLongMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}
jobject AndroidUtils::CallJniObjectMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniObjectMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	jobject Result = Env->CallStaticObjectMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}
jobjectArray AndroidUtils::CallJniObjectArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniObjectArray [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	jobjectArray Result = static_cast<jobjectArray>(Env->CallStaticObjectMethodV(Class, Method, Args));
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}
jfloatArray AndroidUtils::CallJniFloatArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniFloatArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	jfloatArray Result = static_cast<jfloatArray>(Env->CallStaticObjectMethodV(Class, Method, Args));
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}
jintArray AndroidUtils::CallJniIntArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJniIntArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	jintArray Result = static_cast<jintArray>(Env->CallStaticObjectMethodV(Class, Method, Args));
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

//=============== Override Callback and Return JNI===========================
// ------------ void
template<typename ...Args>
void AndroidUtils::CallVoidJni(const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	CallJniVoidMethod(ClassName, MethodName, MethodSignature, args...);
}

// ------------ FString
template<typename ...Args>
FString AndroidUtils::CallJNI(FString str, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	return CallJniStringMethod(ClassName, MethodName, MethodSignature, args...);
}
// ------------ string
template<typename ...Args>
string AndroidUtils::CallJNI(string str, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	FString TempStr = CallJniStringMethod(ClassName, MethodName, MethodSignature, args...);
	return string(TCHAR_TO_UTF8(*TempStr));
}
// ------------ bool
template<typename ...Args>
bool AndroidUtils::CallJNI(bool b, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	return CallJniBoolMethod(ClassName, MethodName, MethodSignature, args...);
}
// ------------ int
template<typename ...Args>
int AndroidUtils::CallJNI(int i, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	return CallJniIntMethod(ClassName, MethodName, MethodSignature, args...);
}
// ------------ long
template<typename ...Args>
long AndroidUtils::CallJNI(long l, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	return CallJniLongMethod(ClassName, MethodName, MethodSignature, args...);
}
// ------------ jobject
template<typename ...Args>
jobject AndroidUtils::CallJNI(jobject jo, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	return CallJniObjectMethod(ClassName, MethodName, MethodSignature, args...);
}
// ------------ TArray<FString>
template<typename ...Args>
TArray<FString> AndroidUtils::CallJNI(TArray<FString> strArr, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	return JavaConvert::ConvertToStringArray(CallJniObjectArrayMethod(ClassName, MethodName, MethodSignature, args...));
}
// ------------ TArray<float>
template<typename ...Args>
TArray<float> AndroidUtils::CallJNI(TArray<float> fArr, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	return JavaConvert::ConvertToFloatArray(CallJniFloatArrayMethod(ClassName, MethodName, MethodSignature, args...));
}
// ------------ TArray<int>
template<typename ...Args>
TArray<int> AndroidUtils::CallJNI(TArray<int> iArr, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	return JavaConvert::ConvertToIntArray(CallJniIntArrayMethod(ClassName, MethodName, MethodSignature, args...));
}


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
template<typename MethodType, typename ...Args>
MethodType AndroidUtils::CallNativeAndroid(const char* ClassName, const char* FunctionName, bool isActivity, Args ...args)
{
	MethodType returnType;

	string MethodSignature = "(";
	MethodSignature += isActivity ? "Landroid/app/Activity;" : "";
	GetType(MethodSignature, args...);
	MethodSignature += ")";
	MethodSignature += GetTypeName(returnType);

	// В случае если функция что-то возвращает -  используйте присовение к переменной = или приведение типов += string(...)
	// If the function returns something, use assignment to the variable = or casting += string(...)
	if (isActivity)
		return CallJNI(returnType, ClassName, FunctionName, MethodSignature.c_str(), FJavaWrapper::GameActivityThis, convertArg(args)...);
	else
		return CallJNI(returnType, ClassName, FunctionName, MethodSignature.c_str(), convertArg(args)...);
}

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
template<typename ...Args>
void AndroidUtils::CallNativeAndroidVoid(const char* ClassName, const char* FunctionName, bool isActivity, Args ...args)
{
	string MethodSignature = "(";
	MethodSignature += isActivity ? "Landroid/app/Activity;" : "";
	GetType(MethodSignature, args...);
	MethodSignature += ")";
	MethodSignature += GetTypeName();

	if (isActivity)
		CallVoidJni(ClassName, FunctionName, MethodSignature.c_str(), FJavaWrapper::GameActivityThis, convertArg(args)...);
	else
		CallVoidJni(ClassName, FunctionName, MethodSignature.c_str(), convertArg(args)...);
}
