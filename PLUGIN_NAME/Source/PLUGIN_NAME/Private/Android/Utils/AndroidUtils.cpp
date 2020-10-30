#include "AndroidUtils.h"

//=============== Call Target Jni ========================================
FString AndroidUtils::CallJniStringMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJni [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	jstring Return = static_cast<jstring>(Env->CallStaticObjectMethodV(Class, Method, Args));
	va_end(Args);

	const char * UTFString = Env->GetStringUTFChars(Return, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(Return, UTFString);
	Env->DeleteLocalRef(Class);

	return Result;
}
bool AndroidUtils::CallJniBoolMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJni [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

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
	UE_LOG(LogTemp, Warning, TEXT("Method CallJni [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

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
	UE_LOG(LogTemp, Warning, TEXT("Method CallJni [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

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
	UE_LOG(LogTemp, Warning, TEXT("Method CallJni [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

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
void AndroidUtils::CallJniVoidMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogTemp, Warning, TEXT("Method CallJni [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jclass Class = FAndroidApplication::FindJavaClass(ClassName);
	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);

	va_list Args;
	va_start(Args, MethodSignature);
	Env->CallStaticVoidMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);
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

//=============== Override Callback and Return JNI===========================
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
// ------------ void
template<typename ...Args>
void AndroidUtils::CallVoidJni(const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
{
	CallJniVoidMethod(ClassName, MethodName, MethodSignature, args...);
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
