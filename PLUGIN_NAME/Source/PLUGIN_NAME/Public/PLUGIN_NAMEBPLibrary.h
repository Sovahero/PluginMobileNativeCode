#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Async/Async.h"
#include "Engine.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <stdio.h>
#include <stdlib.h>

#include "PLUGIN_NAMEBPLibrary.generated.h"

using namespace std;

#if PLATFORM_ANDROID
//В версии 4.24 и ниже используется gnustl в котором поддержка c++11 неполная
//Нужный функционал дописывается самостоятельно в этом блоке
// In version 4.24 and below, gnustl is used in which C++11 support is incomplete
// the Necessary functionality is added independently in this block
#if ENGINE_MINOR_VERSION<=24 //----------------------
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}
#endif //-------------------------------------------------------------
#endif //Android

//Диспатчер/Dispatcher
//-------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_DELEGATE_OneParam(FTypeDispacth, FString, ReturnValue);
//------------------------------------------------------------------------------------------------------------

UENUM(BlueprintType)
enum ToastLength
{
	Short = 0 UMETA(DisplayName = "Short"),
	Long = 1 UMETA(DisplayName = "Long"),
};

UCLASS()
class UPLUGIN_NAMEBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:

	//---Диспатчер/Dispatcher ---
	static void FStaticFunctDispatch(FString ReturnValue);
	static FTypeDispacth FStaticValueDispatch;
	//----------------------------------

	//==== Переменные класса/Class variable==========================================


	//==== Прототип класса/The prototype of the class ===================================
	UFUNCTION(BlueprintCallable, Category = "PLUGIN_NAME Category")
		static void asyncHelloWorld(const FTypeDispacth& CallBackDispatch, FString String = "async Hello World");

	UFUNCTION(BlueprintCallable, Category = "PLUGIN_NAME Category")
		static FString HelloWorld(FString String = "Hello World");

	UFUNCTION(BlueprintCallable, Category = "PLUGIN_NAME Category")
		static void ShowToastMobile(FString String, ToastLength length);
};
