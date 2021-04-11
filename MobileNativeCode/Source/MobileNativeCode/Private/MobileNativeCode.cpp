#include "MobileNativeCode.h"

#define LOCTEXT_NAMESPACE "FMobileNativeCodeModule"

void FMobileNativeCodeModule::StartupModule()
{
	// This code will be executed after loading your module into memory; the exact time is specified in the .plugin file for each module.
}

void FMobileNativeCodeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMobileNativeCodeModule, MobileNativeCode)