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
#include "IOS/Utils/ObjC_Convert.h"

#include "IOS/ObjC/TestIosClass.h"
#endif


//==== Тело класса / Class body ==============================================
UPLUGIN_NAMEBPLibrary::UPLUGIN_NAMEBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}



// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
	String = ObjConvert::ToFString( [TestIosClass HelloWorldOnIOS: String.GetNSString()] );
#endif// IOS

	return String;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//==== Иницализация статичских переменных / Initialization of static variables===========
FTypeDispacth UPLUGIN_NAMEBPLibrary::FStaticValueDispatch;

//------- Асинхронный вызов нативного кода / Asynchronous calling of native code ------
void UPLUGIN_NAMEBPLibrary::asyncHelloWorld(const FTypeDispacth& CallBackDispatch, FString String)
{
	UPLUGIN_NAMEBPLibrary::FStaticValueDispatch = CallBackDispatch;

#if PLATFORM_ANDROID
	AndroidUtils::CallNativeAndroidVoid("com/epicgames/ue4/TestJavaClass", "asyncHelloWorldOnAndroid", true, String);
#endif //Android

#if PLATFORM_IOS	
	[TestIosClass asyncHelloWorldOnIOS: String.GetNSString()];
#endif // IOS
}

//------- Нативные функции Java кода / Native functions in Java code ---------
#if PLATFORM_ANDROID
JNI_METHOD void Java_com_epicgames_ue4_TestJavaClass_CallBackCPP(JNIEnv* env, jclass clazz, jstring returnStr)
{
	FString result = JavaConvert::FromJavaFString(returnStr);
	UE_LOG(LogTemp, Warning, TEXT("asyncHelloWorld callback caught in C++! - [%s]"), *FString(result)); //Debug log for UE4
	UPLUGIN_NAMEBPLibrary::FStaticFunctDispatch(result);//Вызвать диспатчер / Call Dispatcher
}
#endif //PLATFORM_ANDROID

//------- функции IOS кода / functions IOS code ---------
#if PLATFORM_IOS
void UPLUGIN_NAMEBPLibrary::CallBackCPP_IOS(NSString* sResult)
{
	FString fResult = ObjConvert::ToFString(sResult);
	UPLUGIN_NAMEBPLibrary::FStaticFunctDispatch(fResult); //Вызвать диспатчер / Call Dispatcher
}
#endif //PLATFORM_IOS


//-------Тело диспатчера / Dispatcher body --------------------------
void UPLUGIN_NAMEBPLibrary::FStaticFunctDispatch(FString FValueReturnDispatch)
{
	//Лямбда функция для диспатчера/Lambda function for the dispatcher
	AsyncTask(ENamedThreads::GameThread, [=]() {
		FStaticValueDispatch.ExecuteIfBound(FValueReturnDispatch);
		});
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// #~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//------- Вызов всплывающего сообщения / Calling a pop-up message ------------------
void UPLUGIN_NAMEBPLibrary::ShowToastMobile(FString String, ToastLengthMessage length)
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
	FString TextForToast = FString("Your message: " + String);

	TextForToast += " Your phone: ";
	TextForToast += ObjConvert::ToFString([TestIosClass getModel]);

	//Вызов функции через паттерн одиночка / Calling a function using the singleton pattern
	[[TestIosClass Singleton]showToast: TextForToast.GetNSString() Duration: length];

#endif// IOS
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// #~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// -------- Пример работы с массивами / Example of working with arrays  ----------------
void UPLUGIN_NAMEBPLibrary::ExampleArray(FString& Arr1, FString& Arr2)
{
	//Работа с массива происходит через TArray/
	//Working with an array is done via TArray

	//Support argType = FString, bool, int, long, float
	TArray<FString> a1;
	TArray<bool> a2;
	TArray<int> a3;
	TArray<long> a4;
	TArray<float> a5;

	//Support returnType = FString, int, float
	TArray<FString> TestStrArr;
#if PLATFORM_ANDROID	
	TestStrArr = AndroidUtils::CallNativeAndroid<TArray<FString>>("com/epicgames/ue4/TestJavaClass", "TestArray", false, a1, a2, a3, a4, a5);
#endif //Android

#if PLATFORM_IOS
	TestStrArr = ObjConvert::NSMutableArrayToTArrayFString(
		[TestIosClass
		TestArray: ObjConvert::TArrayFStringToNSMutableArray(a1)
		b: ObjConvert::TArrayNumToNSMutableArray(a2)
		i: ObjConvert::TArrayNumToNSMutableArray(a3)
		f: ObjConvert::TArrayNumToNSMutableArray(a4)
		l: ObjConvert::TArrayNumToNSMutableArray(a5)
		]);
#endif //PLATFORM_IOS

	Arr1 = TestStrArr[0];
	Arr2 = TestStrArr[1];
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// #~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//---------- Получить абсолютный путь к папке для сохранения файлов /
//---------- Get the absolute path to the folder to save files to
FString UPLUGIN_NAMEBPLibrary::GetAbsolutePathTmpFolder(FString NameFile)
{
#if PLATFORM_ANDROID
	// "storage/emulated/0/Android/data/data/%PROJECT_NAME%/"
	FString sPath = AndroidUtils::CallNativeAndroid<FString>("com/epicgames/ue4/TestJavaClass", "GetExternalFilesDir", true);
	return sPath + NameFile;
#endif //Android

#if PLATFORM_IOS
	// "/var/mobile/Containers/Data/Application/23D4996A6-BCC9-4C2F-A8B4-306BEB087BDB/Library/Caches/"
	FString sPath = ObjConvert::ToFString([TestIosClass getTmpFilePath]);
	return sPath + NameFile;
#endif //PLATFORM_IOS

	return TEXT("ERR");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
