#include "PLUGIN_NAMEBPLibrary.h"
#include "PLUGIN_NAME.h"
#include "Async/Async.h"
#include "Engine.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJava.h"

#include "Android/Utils/AndroidUtils.h"
#endif

#if PLATFORM_IOS

#endif

//==== Иницализация статичских переменных / Initialization of static variables===========
FTypeDispacth UPLUGIN_NAMEBPLibrary::FStaticValueDispatch;

//==== Тело класса / Class body==============================================
UPLUGIN_NAMEBPLibrary::UPLUGIN_NAMEBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


//------- Синхронный вызов нативного кода / Synchronous invocation of native code -------
FString UPLUGIN_NAMEBPLibrary::HelloWorld(FString String)
{
#if PLATFORM_ANDROID	
	/* 
	* "com/epicgames/ue4/TestJavaClass" - package(используется com/epicgames/ue4) и имя вашего Java класса / package (used by com/epicgames/ue4) and the name of your Java class.
	* "HelloWorldOnAndroid" - Имя вашей Java функции / Name of your Java function.
	* false - Определяет нужно ли передавать Activity UE4 в Java / Determines whether to pass Activity UE4 to Java.
	* String -
	* Список ваших параметров в Java функции(если тип переменной в Java коде специфичный например jobject,
	* его следует перед вызовом функции переконвертировать) /
	* A list of your parameters in the Java function(if the variable type in the Java code is specific, such as jobject, it should be converted before calling the function).
	*/
	String = AndroidUtils::CallNativeAndroid<FString>("com/epicgames/ue4/TestJavaClass", "HelloWorldOnAndroid", false, String);

#endif //Android

#if PLATFORM_IOS

#endif// IOS

	return String;
}

//------- Асинхронный вызов нативного кода / Asynchronous calling of native code ------
void UPLUGIN_NAMEBPLibrary::asyncHelloWorld(const FTypeDispacth& CallBackDispatch, FString String)
{
	UPLUGIN_NAMEBPLibrary::FStaticValueDispatch = CallBackDispatch;

#if PLATFORM_ANDROID
	AndroidUtils::CallNativeAndroidVoid("com/epicgames/ue4/TestJavaClass", "asyncHelloWorldOnAndroid", true, String);

#endif //Android

#if PLATFORM_IOS

#endif// IOS
}

//------- Нативные функции Java кода / Native functions in Java code ---------
#if PLATFORM_ANDROID
JNI_METHOD void Java_com_epicgames_ue4_TestJavaClass_CallBackCPP(JNIEnv* env, jclass clazz, jstring returnStr)
{
	FString result = JavaConvert::FromJavaFString(returnStr);
	UE_LOG(LogTemp, Warning, TEXT("asyncHelloWorld callback caught in C++! - [%s]"), *FString(result));
	UPLUGIN_NAMEBPLibrary::FStaticFunctDispatch(result);//Вызвать диспатчер
}
#endif //PLATFORM_ANDROID

//-------Тело диспатчера / Dispatcher body --------------------------
void UPLUGIN_NAMEBPLibrary::FStaticFunctDispatch(FString FValueReturnDispatch)
{
	//Лямбда функция для диспатчера/Lambda function for the dispatcher
	AsyncTask(ENamedThreads::GameThread, [=]() {
		FStaticValueDispatch.ExecuteIfBound(FValueReturnDispatch);
		});
}

//------- Вызов всплывающего сообщения / Calling a pop-up message ------------------
void UPLUGIN_NAMEBPLibrary::ShowToastMobile(FString String, ToastLength length)
{
#if PLATFORM_ANDROID
	FString TextForToast = FString("Your message: " + String);

	TextForToast += " Your phone: ";
	TextForToast += FString(AndroidUtils::CallNativeAndroid<FString>("com/epicgames/ue4/TestJavaClass", "getBrand", false));
	TextForToast += " " + FString(AndroidUtils::CallNativeAndroid<FString>("com/epicgames/ue4/TestJavaClass", "getModel", false));
	TextForToast += " ID: ";
	TextForToast += FString(AndroidUtils::CallNativeAndroid<FString>("com/epicgames/ue4/TestJavaClass", "getAndroidId", true));

	AndroidUtils::CallNativeAndroidVoid("com/epicgames/ue4/TestJavaClass", "showToast", true, TextForToast, length);

#endif //Android

#if PLATFORM_IOS

#endif// IOS
}
