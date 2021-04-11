#include "MobileNativeCodeBlueprint.h"
#include "MobileNativeCode.h"
#include <Async/Async.h>
#include <Engine.h>

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// All Java classes are on the path: "MobileNativeCode\Source\MobileNativeCode\Private\Android\Java\"
// All Objective-C classes are on the path: "MobileNativeCode\Source\MobileNativeCode\Private\IOS\ObjC\"

#if PLATFORM_ANDROID
#include "Android/Utils/AndroidUtils.h"
#endif

#if PLATFORM_IOS
#include "IOS/Utils/ObjC_Convert.h"

#include "IOS/ObjC/IosHelloWorld.h"
#include "IOS/ObjC/IosAsyncHelloWorld.h"
#include "IOS/ObjC/IosNativeUI.h"
#include "IOS/ObjC/IosExampleArray.h"
#include "IOS/ObjC/IosDeviceInfo.h"
#endif

#if PLATFORM_ANDROID
// In version 4.24 and below, gnustl is used in which C++11 support is incomplete
// the Necessary functionality is added independently in this block

#if ENGINE_MINOR_VERSION<=24//

template <typename T>
std::string to_string(T value)
{
  std::ostringstream os;
  os << value;
  return os.str();
}

#endif

#endif //Android


// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FString UMobileNativeCodeBlueprint::HelloWorld(FString MyStr /*= "Hello World"*/)
{
#if PLATFORM_ANDROID

  MyStr = AndroidUtils::CallJavaCode<FString>(
    "com/Plugins/MobileNativeCode/HelloWorldClass",     // package (used by com/Plugins/MobileNativeCode) and the name of your Java class.
    "HelloWorldOnAndroid",                                                //Name of your Java function.
    "",                                                                                     //Set your own signature instead of an automatic one (Send an empty one if you need an automatic one).
    false,                                                                                 //Determines whether to pass Activity UE4 to Java.
    MyStr                                                                               //A list of your parameters in the Java function.
  );

#endif //Android


#if PLATFORM_IOS

  //The Objective-C language can be mixed with C++ in a single file
  MyStr = FString([IosHelloWorld HelloWorldOnIOS : MyStr.GetNSString()]);

#endif// IOS

  return MyStr;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//--  Initialization of static variables
FTypeDispacth UMobileNativeCodeBlueprint::StaticValueDispatch;


void UMobileNativeCodeBlueprint::asyncHelloWorld(const FTypeDispacth& CallBackPlatform, FString MyStr /*= "async Hello World"*/)
{
  UMobileNativeCodeBlueprint::StaticValueDispatch = CallBackPlatform;

#if PLATFORM_ANDROID

  AndroidUtils::CallJavaCode<void>(
    "com/Plugins/MobileNativeCode/asyncHelloWorldClass",
    "asyncHelloWorldOnAndroid",
    "",
    true,
    MyStr
  );

#endif //Android


#if PLATFORM_IOS

  [IosAsyncHelloWorld asyncHelloWorldOnIOS : MyStr.GetNSString()];

#endif // IOS
}

void UMobileNativeCodeBlueprint::StaticFunctDispatch(const FString& ReturnValue)
{  
  //Lambda function for the dispatcher
  AsyncTask(ENamedThreads::GameThread, [=]() {
    StaticValueDispatch.ExecuteIfBound(ReturnValue);
    });
}

//-- Functions CallBack for Java code
#if PLATFORM_ANDROID
JNI_METHOD void Java_com_Plugins_MobileNativeCode_asyncHelloWorldClass_CallBackCppAndroid(JNIEnv* env, jclass clazz, jstring returnStr)
{
  FString result = JavaConvert::FromJavaFString(returnStr);
  UE_LOG(LogTemp, Warning, TEXT("asyncHelloWorld callback caught in C++! - [%s]"), *FString(result)); //Debug log for UE4
  UMobileNativeCodeBlueprint::StaticFunctDispatch(result);// Call Dispatcher
}
#endif //PLATFORM_ANDROID

//-- Functions CallBack for iOS code
#if PLATFORM_IOS
void UMobileNativeCodeBlueprint::CallBackCppIOS(NSString* sResult)
{
  FString fResult = FString(sResult);
  UE_LOG(LogTemp, Warning, TEXT("asyncHelloWorld callback caught in C++! - [%s]"), *FString(fResult)); //Debug log for UE4
  UMobileNativeCodeBlueprint::StaticFunctDispatch(fResult); // Call Dispatcher
}
#endif //PLATFORM_IOS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void UMobileNativeCodeBlueprint::ShowToastMobile(FString Message, EToastLengthMessage Length)
{
#if PLATFORM_ANDROID

  AndroidUtils::CallJavaCode<void>("com/Plugins/MobileNativeCode/NativeUI", "showToast", "", true, Message, (int)Length);

#endif //Android

#if PLATFORM_IOS

  // Calling a function using the singleton pattern
  [[IosNativeUI Singleton]showToast:Message.GetNSString() Duration : (int)Length];

#endif // IOS
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void UMobileNativeCodeBlueprint::ExampleArray(FString& Arr1, FString& Arr2)
{
  //Working with an array is done via TArray

  //Support argType = FString, bool, int, long, float, const char*, std::string
  TArray<FString> a1;
  TArray<bool> a2;
  TArray<int> a3;
  TArray<long> a4;
  TArray<float> a5;

  //Support returnType = FString, int, float, long
  TArray<FString> TestStrArr;

#if PLATFORM_ANDROID

  TestStrArr = AndroidUtils::CallJavaCode<TArray<FString>>(
    "com/Plugins/MobileNativeCode/ExampleArrayClass",             // package (used by com/Plugins/MobileNativeCode) and the name of your Java class.
    "TestArray",                                                                                  // Name of your Java function.
    "",                                                                                                  // Set your own signature instead of an automatic one (Send an empty one if you need an automatic one).
    false,                                                                                              // Determines whether to pass Activity UE4 to Java.
    a1, a2, a3, a4, a5                                                                            //A list of your parameters in the Java function.
  );

#endif //Android


#if PLATFORM_IOS

  //The Objective-C language can be mixed with C++ in a single file
  TestStrArr = ObjCconvert::NSMutableArrayToTArrayFString([IosExampleArray    
      TestArray : ObjCconvert::TArrayFStringToNSMutableArray(a1)
                    b : ObjCconvert::TArrayNumToNSMutableArray(a2)
                    i : ObjCconvert::TArrayNumToNSMutableArray(a3)
                    f : ObjCconvert::TArrayNumToNSMutableArray(a4)
                    l : ObjCconvert::TArrayNumToNSMutableArray(a5)
    ]);

#endif // iOS

  Arr1 = TestStrArr[0];
  Arr2 = TestStrArr[1];
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// #~~~~~~~~~~~~~~~~~~~~~~~~~~~ begin 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FString UMobileNativeCodeBlueprint::GetDeviceInfo()
{
  FString sDeviceInfo;

#if PLATFORM_ANDROID

  sDeviceInfo += " Your phone: ";
  sDeviceInfo += AndroidUtils::CallJavaCode<FString>("com/Plugins/MobileNativeCode/DeviceInfo", "getBrand", "", false);
  sDeviceInfo += " " + AndroidUtils::CallJavaCode<FString>("com/Plugins/MobileNativeCode/DeviceInfo", "getModel", "", false);
    
  sDeviceInfo += " Path to save files: ";
  // "storage/emulated/0/Android/data/data/%PROJECT_NAME%/"
  sDeviceInfo += AndroidUtils::CallJavaCode<FString>("com/Plugins/MobileNativeCode/DeviceInfo", "GetExternalFilesDir", "", true);

#endif //Android


#if PLATFORM_IOS

  sDeviceInfo += " Your phone: ";
  sDeviceInfo += FString([IosDeviceInfo getModel]);
    
  sDeviceInfo += " Path to save files: ";
  // "/var/mobile/Containers/Data/Application/%PROJECT_ID%/Library/Caches/"
  sDeviceInfo += FString([IosDeviceInfo getTmpFilePath]);

#endif //PLATFORM_IOS

  return sDeviceInfo;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void UMobileNativeCodeBlueprint::ExampleMyJavaObject(FString& JavaBundle)
{
#if PLATFORM_ANDROID

  // Creating an empty jobject object, assigning it the standard java Bundle class
  // Bundle: https://developer.android.com/reference/android/os/Bundle

  //In order to populate a jobject with a Java class, you need to return it from your static Java function.

  jobject myJavaObject = AndroidUtils::CallJavaCode<jobject>(
    "com/Plugins/MobileNativeCode/MyJavaObjects",  // package (used by com/Plugins/MobileNativeCode) and the name of your Java class.
    "getBundleJava",                                                        // Name of your Java function.
    "()Landroid/os/Bundle;",                                            // Set your own signature instead of an automatic one (Send an empty one if you need an automatic one).
    false                                                                            // Determines whether to pass Activity UE4 to Java.
    );

  // Functions such as putString and putDouble are defined inside Bunde. Let's call them with our parameters:

  AndroidUtils::CallJavaCode<void>(
    myJavaObject,         // the type of jobject from which you want to call a local Java function
    "putFloat",               // Name of Java function.
    "",                            // Set your own signature instead of an automatic one (Send an empty one if you need an automatic one).
    "myKey", 1234.f     // A list of your parameters in the Java function.
    );

  AndroidUtils::CallJavaCode<void>(
    myJavaObject,
    "putString",
    "",
    "myKey2", "myValueForBundle"
    );


  // Let's see what's inside our Bundle
  JavaBundle = AndroidUtils::CallJavaCode<FString>(
    myJavaObject,         // the type of jobject from which you want to call a local Java function
    "toString",               // Name of Java function.
    ""                             // Set your own signature instead of an automatic one (Send an empty one if you need an automatic one).
    );

  // After you have finished working with your jobject, you need to delete it
  AndroidUtils::DeleteJavaObject(myJavaObject);

#endif //Android
}
