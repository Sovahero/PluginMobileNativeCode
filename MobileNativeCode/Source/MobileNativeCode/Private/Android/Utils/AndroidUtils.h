#pragma once

#include <Android/AndroidJNI.h>
#include <Android/AndroidApplication.h>
#include <Android/AndroidJava.h>

#include "JavaConvert.h"
#include "MobileNativeCodeBlueprint.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;
class AndroidUtils



{
private:
  static bool m_supportedPlatform;

public:
  static void Initialization()
  {
    m_supportedPlatform = true;
    m_supportedPlatform = (bool)CallJavaCode<int>(
      "com/Plugins/MobileNativeCode/MobileNativeCode",
      "Initialization",
      "",
      false
    );

    if(!m_supportedPlatform)
    {
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> The mobile platform is not supported, all further Java functions will not be called!"));
    }
    else
    {
      UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Init on phone: %s"), *UMobileNativeCodeBlueprint::GetModelDevice());
    }
  }

  //Can the mobile platform call functions
  static int isSupportPlatform()
  {
    if(!m_supportedPlatform)
    {
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> The mobile platform is not supported, all further Java functions will not be called!"));
    }
    return m_supportedPlatform;
  }

  //-- Free memory
  static bool DeleteJavaObject(jobject JavaObject)
  {
    if(JavaObject)
    {
      JNIEnv* Env = FAndroidApplication::GetJavaEnv();
      Env->DeleteLocalRef(JavaObject);
      JavaObject = nullptr;
      return true;
    }
    return false;
  }

  // -- Why do we need this structure?
  // -- https://stackoverflow.com/questions/47373354/c-void-argument-with-variadic-template
  template <typename T>
  struct type { };

  template<typename anyType>
  static const anyType& convertArg(const anyType& value)
  {
    return value;
  }
  static jstring convertArg(const char* str)
  {
    return JavaConvert::GetJavaString(str);
  }
  static jstring convertArg(const std::string& str)
  {
    return JavaConvert::GetJavaString(str);
  }
  static jstring convertArg(const FString& str)
  {
    return JavaConvert::GetJavaString(str);
  }
  static jlong convertArg(long l)
  {
    return JavaConvert::GetJavaLong(l);
  }
  //---array
  static jobjectArray convertArg(const TArray<const char*>& stringArray)
  {
    TArray<FString> tmpFString;
    for (auto tmpCellStringArray : stringArray) {
      std::string tmpString = tmpCellStringArray;
      tmpFString.Add(tmpString.c_str());
    }
    return JavaConvert::ConvertToJStringArray(tmpFString);
  }
  static jobjectArray convertArg(const TArray<std::string>& stringArray)
  {
    TArray<FString> tmpFString;
    for (auto tmpCellStringArray : stringArray)
      tmpFString.Add(tmpCellStringArray.c_str());

    return JavaConvert::ConvertToJStringArray(tmpFString);
  }
  static jobjectArray convertArg(const TArray<FString>& stringArray)
  {
    return JavaConvert::ConvertToJStringArray(stringArray);
  }
  static jbooleanArray convertArg(const TArray<bool>& boolArray)
  {
    return JavaConvert::ConvertToJBooleanArray(boolArray);
  }
  static jintArray convertArg(const TArray<int>& intArray)
  {
    return JavaConvert::ConvertToJIntArray(intArray);
  }
  static jbyteArray convertArg(const TArray<uint8>& byteArray)
  {
    return JavaConvert::ConvertToJByteArray(byteArray);
  }
  static jlongArray convertArg(const TArray<long>& longArray)
  {
    return JavaConvert::ConvertToJLongArray(longArray);
  }
  static jfloatArray convertArg(const TArray<float>& floatArray)
  {
    return JavaConvert::ConvertToJFloatArray(floatArray);
  }


  ///=============== Override Tempalte===========================
  static std::string GetTypeName(void)
  {
    return "V";
  }
  static std::string GetTypeName(bool)
  {
    return "Z";
  }
  static std::string GetTypeName(unsigned char)
  {
    return "B";
  }
  static std::string GetTypeName(char)
  {
    return "C";
  }
  static std::string GetTypeName(short)
  {
    return "S";
  }
  static std::string GetTypeName(int)
  {
    return "I";
  }
  static std::string GetTypeName(unsigned int)
  {
    return "I";
  }
  static std::string GetTypeName(long)
  {
    return "J";
  }
  static std::string GetTypeName(float)
  {
    return "F";
  }
  static std::string GetTypeName(double)
  {
    return "D";
  }
  static std::string GetTypeName(const char*)
  {
    return "Ljava/lang/String;";
  }
  static std::string GetTypeName(const std::string&)
  {
    return "Ljava/lang/String;";
  }
  static std::string GetTypeName(const FString&)
  {
    return "Ljava/lang/String;";
  }
  static std::string GetTypeName(jstring)
  {
    return "Ljava/lang/String;";
  }
  static std::string GetTypeName(jobject)
  {
    return "Ljava/lang/Object;";
  }

  //----array
  static std::string GetTypeName(jobjectArray)
  {
    return "[Ljava/lang/Object;";
  }
  template<typename anyType>
  static std::string GetTypeName(const TArray<anyType>&)
  {
    anyType SymbolType{};
    return std::string("[" + GetTypeName(SymbolType));
  }
  template<typename anyType>
  static std::string GetTypeName(const vector<anyType>&)
  {
    anyType SymbolType{};
    return std::string("[" + GetTypeName(SymbolType));
  }
  

  ///=============== Recursion Method for Variadic Template===========================
  // ------------ GetType
  template<typename anyType, typename ...Args>
  static void GetType(std::string& signatureString, anyType value, Args ...args)
  {
    signatureString += GetTypeName(value);
    GetType(signatureString, args...);
  }
  // ------------ GetType
  static void GetType(std::string&) {   }


  ///=============== Call Target Jni ========================================
  //========== UserObjectClass ==============
  static void CallJniVoidMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniVoidMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    Env->CallStaticVoidMethodV(Class, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);
  }

  static FString CallJniStringMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return TEXT("");

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniStringMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return TEXT("");
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return TEXT("");
#endif

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
  static bool CallJniBoolMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return false;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniBoolMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return false;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return false;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    bool Result = Env->CallStaticBooleanMethodV(Class, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static int CallJniIntMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return 0;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniIntMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return 0;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return 0;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    int Result = Env->CallStaticIntMethodV(Class, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static long CallJniLongMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return 0;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniLongMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return 0;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return 0;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    long Result = Env->CallStaticLongMethodV(Class, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static jobject CallJniObjectMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniObjectMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jobject Result = Env->CallStaticObjectMethodV(Class, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);
    if (!Result)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));


    return Result;
  }
  static jobjectArray CallJniObjectArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniObjectArray [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jobjectArray Result = static_cast<jobjectArray>(Env->CallStaticObjectMethodV(Class, Method, Args));
    va_end(Args);

    Env->DeleteLocalRef(Class);
    if (!Result)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobjectArray = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    return Result;
  }
  static jfloatArray CallJniFloatArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniFloatArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jfloatArray Result = static_cast<jfloatArray>(Env->CallStaticObjectMethodV(Class, Method, Args));
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static jintArray CallJniIntArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniIntArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jintArray Result = static_cast<jintArray>(Env->CallStaticObjectMethodV(Class, Method, Args));
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static jlongArray CallJniLongArrayMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallJniLongArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = FAndroidApplication::FindJavaClass(ClassName);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jlongArray Result = static_cast<jlongArray>(Env->CallStaticObjectMethodV(Class, Method, Args));
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }

  //========== JavaObjectClass ==============
  static void CallObjectJniVoidMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniVoidMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    Env->CallVoidMethodV(object, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);
  }

  static FString CallObjectJniStringMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return TEXT("");

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniStringMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return TEXT("");
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return TEXT("");
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jstring Return = static_cast<jstring>(Env->CallObjectMethodV(object, Method, Args));
    va_end(Args);

    const char* UTFString = Env->GetStringUTFChars(Return, nullptr);
    FString Result(UTF8_TO_TCHAR(UTFString));
    Env->ReleaseStringUTFChars(Return, UTFString);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static bool CallObjectJniBoolMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return false;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniBoolMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return false;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return false;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    bool Result = Env->CallBooleanMethodV(object, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static int CallObjectJniIntMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return 0;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniIntMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return 0;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return 0;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    int Result = Env->CallIntMethodV(object, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static long CallObjectJniLongMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return 0;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniLongMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return 0;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return 0;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    long Result = Env->CallLongMethodV(object, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static jobject CallObjectJniObjectMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniObjectMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jobject Result = Env->CallObjectMethodV(object, Method, Args);
    va_end(Args);

    Env->DeleteLocalRef(Class);

    if (!Result)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: return jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    return Result;
  }
  static jobjectArray CallObjectJniObjectArrayMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniObjectArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jobjectArray Result = static_cast<jobjectArray>(Env->CallObjectMethodV(object, Method, Args));
    va_end(Args);

    Env->DeleteLocalRef(Class);
    if (!Result)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: return jobjectArray = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    return Result;
  }
  static jfloatArray CallObjectJniFloatArrayMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniFloatArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jfloatArray Result = static_cast<jfloatArray>(Env->CallObjectMethodV(object, Method, Args));
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static jintArray CallObjectJniIntArrayMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniIntArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));
    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jintArray Result = static_cast<jintArray>(Env->CallObjectMethodV(object, Method, Args));
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }
  static jlongArray CallObjectJniLongArrayMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
  {
    if (!m_supportedPlatform)
      return nullptr;

    UE_LOG(LogTemp, Log, TEXT("MobileNativeCode -> Method CallObjectJniLongArrayMethod [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    if (!object)
      UE_LOG(LogTemp, Error, TEXT("MobileNativeCode -> Err: jobject = null  [%s][%s]"), *FString(MethodName), *FString(MethodSignature));

    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    jclass Class = Env->GetObjectClass(object);
#if UE_BUILD_SHIPPING
    if (!Class) return nullptr;
#endif
    jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, false);
#if UE_BUILD_SHIPPING
    if (!Method) return nullptr;
#endif

    va_list Args;
    va_start(Args, MethodSignature);
    jlongArray Result = static_cast<jlongArray>(Env->CallObjectMethodV(object, Method, Args));
    va_end(Args);

    Env->DeleteLocalRef(Class);

    return Result;
  }


  ///=============== Override Callback and Return JNI===========================
  //========== UserObjectClass ==============

  // ------------ void case
  template <typename... Args>
  static void isTypeJNI(type<void>, const char* ClassName, const char* FunctionName, std::string OverrideSignature, bool isActivity, Args ...args)
  {
    std::string MethodSignature;
    if (OverrideSignature.empty()) {
      MethodSignature = "(";
      MethodSignature += isActivity ? "Landroid/app/Activity;" : "";
      GetType(MethodSignature, args...);
      MethodSignature += ")";
      MethodSignature += GetTypeName();
    }
    else
    {
      MethodSignature = OverrideSignature;
    }

    if (isActivity)
      CallJniVoidMethod(ClassName, FunctionName, MethodSignature.c_str(), FJavaWrapper::GameActivityThis, convertArg(args)...);
    else
      CallJniVoidMethod(ClassName, FunctionName, MethodSignature.c_str(), convertArg(args)...);
  }

  // ------------ non-void case
  template <typename MethodType, typename... Args>
  static MethodType isTypeJNI(type<MethodType>, const char* ClassName, const char* FunctionName, std::string OverrideSignature, bool isActivity, Args ...args)
  {
    MethodType returnType{};

    std::string MethodSignature;
    if (OverrideSignature.empty()) {
      MethodSignature = "(";
      MethodSignature += isActivity ? "Landroid/app/Activity;" : "";
      GetType(MethodSignature, args...);
      MethodSignature += ")";
      MethodSignature += GetTypeName(returnType);
    }
    else
    {
      MethodSignature = OverrideSignature;
    }

    if (isActivity)
      return CallJNI(returnType, ClassName, FunctionName, MethodSignature.c_str(), FJavaWrapper::GameActivityThis, convertArg(args)...);
    else
      return CallJNI(returnType, ClassName, FunctionName, MethodSignature.c_str(), convertArg(args)...);
  }

  // ------------ FString
  template<typename ...Args>
  static FString CallJNI(const FString&, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallJniStringMethod(ClassName, MethodName, MethodSignature, args...);
  }
  // ------------ std::string
  template<typename ...Args>
  static std::string CallJNI(const std::string&, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    FString TempStr = CallJniStringMethod(ClassName, MethodName, MethodSignature, args...);
    return std::string(TCHAR_TO_UTF8(*TempStr));
  }
  // ------------ bool
  template<typename ...Args>
  static bool CallJNI(bool, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallJniBoolMethod(ClassName, MethodName, MethodSignature, args...);
  }
  // ------------ int
  template<typename ...Args>
  static int CallJNI(int, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallJniIntMethod(ClassName, MethodName, MethodSignature, args...);
  }
  // ------------ long
  template<typename ...Args>
  static long CallJNI(long, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallJniLongMethod(ClassName, MethodName, MethodSignature, args...);
  }
  // ------------ jobject
  template<typename ...Args>
  static jobject CallJNI(jobject, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallJniObjectMethod(ClassName, MethodName, MethodSignature, args...);
  }
  // ------------ jobjectArray
  template<typename ...Args>
  static jobjectArray CallJNI(jobjectArray, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallJniObjectArrayMethod(ClassName, MethodName, MethodSignature, args...);
  }
  // ------------ TArray<FString>
  template<typename ...Args>
  static TArray<FString> CallJNI(const TArray<FString>&, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return JavaConvert::ConvertToStringArray(CallJniObjectArrayMethod(ClassName, MethodName, MethodSignature, args...));
  }
  // ------------ TArray<float>
  template<typename ...Args>
  static TArray<float> CallJNI(const TArray<float>&, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return JavaConvert::ConvertToFloatArray(CallJniFloatArrayMethod(ClassName, MethodName, MethodSignature, args...));
  }
  // ------------ TArray<int>
  template<typename ...Args>
  static TArray<int> CallJNI(const TArray<int>&, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return JavaConvert::ConvertToIntArray(CallJniIntArrayMethod(ClassName, MethodName, MethodSignature, args...));
  }
  // ------------ TArray<long>
  template<typename ...Args>
  static TArray<long> CallJNI(const TArray<long>&, const char* ClassName, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return JavaConvert::ConvertToLongArray(CallJniLongArrayMethod(ClassName, MethodName, MethodSignature, args...));
  }


  //========== JavaObjectClass ==============

  // ------------ void case object
  template <typename... Args>
  static void isTypeJNI(type<void>, jobject JavaObjectClass, const char* FunctionName, std::string OverrideSignature, Args ...args)
  {
    std::string MethodSignature;
    if (OverrideSignature.empty()) {
      MethodSignature = "(";
      GetType(MethodSignature, args...);
      MethodSignature += ")";
      MethodSignature += GetTypeName();
    }
    else
    {
      MethodSignature = OverrideSignature;
    }

    CallObjectJniVoidMethod(JavaObjectClass, FunctionName, MethodSignature.c_str(), convertArg(args)...);
  }

  // ------------ non-void case object
  template <typename MethodType, typename... Args>
  static MethodType isTypeJNI(type<MethodType>, jobject JavaObjectClass, const char* FunctionName, std::string OverrideSignature, Args ...args)
  {
    MethodType returnType{};

    std::string MethodSignature;
    if (OverrideSignature.empty()) {
      MethodSignature = "(";
      GetType(MethodSignature, args...);
      MethodSignature += ")";
      MethodSignature += GetTypeName(returnType);
    }
    else
    {
      MethodSignature = OverrideSignature;
    }

    return CallObjectJNI(returnType, JavaObjectClass, FunctionName, MethodSignature.c_str(), convertArg(args)...);
  }

  // ------------ FString
  template<typename ...Args>
  static FString CallObjectJNI(const FString&, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallObjectJniStringMethod(JavaObjectClass, MethodName, MethodSignature, args...);
  }
  // ------------ std::string
  template<typename ...Args>
  static std::string CallObjectJNI(const std::string&, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    FString TempStr = CallObjectJniStringMethod(JavaObjectClass, MethodName, MethodSignature, args...);
    return std::string(TCHAR_TO_UTF8(*TempStr));
  }
  // ------------ bool
  template<typename ...Args>
  static bool CallObjectJNI(bool, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallObjectJniBoolMethod(JavaObjectClass, MethodName, MethodSignature, args...);
  }
  // ------------ int
  template<typename ...Args>
  static int CallObjectJNI(int, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallObjectJniIntMethod(JavaObjectClass, MethodName, MethodSignature, args...);
  }
  // ------------ long
  template<typename ...Args>
  static long CallObjectJNI(long, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallObjectJniLongMethod(JavaObjectClass, MethodName, MethodSignature, args...);
  }
  // ------------ jobject
  template<typename ...Args>
  static jobject CallObjectJNI(jobject, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallObjectJniObjectMethod(JavaObjectClass, MethodName, MethodSignature, args...);
  }
  // ------------ jobjectArray
  template<typename ...Args>
  static jobjectArray CallObjectJNI(jobjectArray, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return CallObjectJniObjectArrayMethod(JavaObjectClass, MethodName, MethodSignature, args...);
  }
  // ------------ TArray<FString>
  template<typename ...Args>
  static TArray<FString> CallObjectJNI(const TArray<FString>&, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return JavaConvert::ConvertToStringArray(CallObjectJniObjectArrayMethod(JavaObjectClass, MethodName, MethodSignature, args...));
  }
  // ------------ TArray<float>
  template<typename ...Args>
  static TArray<float> CallObjectJNI(const TArray<float>&, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return JavaConvert::ConvertToFloatArray(CallObjectJniFloatArrayMethod(JavaObjectClass, MethodName, MethodSignature, args...));
  }
  // ------------ TArray<int>
  template<typename ...Args>
  static TArray<int> CallObjectJNI(const TArray<int>&, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return JavaConvert::ConvertToIntArray(CallObjectJniIntArrayMethod(JavaObjectClass, MethodName, MethodSignature, args...));
  }
  // ------------ TArray<long>
  template<typename ...Args>
  static TArray<long> CallObjectJNI(const TArray<long>&, jobject JavaObjectClass, const char* MethodName, const char* MethodSignature, Args ...args)
  {
    return JavaConvert::ConvertToLongArray(CallObjectJniLongArrayMethod(JavaObjectClass, MethodName, MethodSignature, args...));
  }


  ///============Calling native Android code from C++===============

  /**
  * @param ClassName - package and the name of your Java class.
  * @param FunctionName -  Name of your Java function.
  * @param OverrideSignature -  Set your own signature instead of an automatic one (Send an empty one if you need an automatic one).
  * @param isActivity -  Determines whether to pass Activity UE4 to Java.
  * @param args... - A list of your parameters in the Java function.
  */
  template<typename MethodType, typename ...Args>
  static MethodType CallJavaCode(const char* ClassName, const char* FunctionName, const char* OverrideSignature, bool isActivity, Args ...args)
  {
    return isTypeJNI(type<MethodType>{}, ClassName, FunctionName, OverrideSignature, isActivity, args...);
  }

  /**
  * @param JavaObjectClass - The object type which you need to call methods from the JAVA API.
  * @param FunctionName -  Name of your Java function.
  * @param OverrideSignature -  Set your own signature instead of an automatic one (Send an empty one if you need an automatic one).
  * @param args... - A list of your parameters in the Java function.
  */
  template<typename MethodType, typename ...Args>
  static MethodType CallJavaCode(jobject JavaObjectClass, const char* FunctionName, const char* OverrideSignature, Args ...args)
  {
    return isTypeJNI(type<MethodType>{}, JavaObjectClass, FunctionName, OverrideSignature, args...);
  }

};
