#include "MobileNativeCode.h"
#include "MobileNativeCodeEditorSettings.h"

#if PLATFORM_ANDROID
#include "Android/Utils/AndroidUtils.h"
#endif

#define LOCTEXT_NAMESPACE "FMobileNativeCodeModule"

/**
 * This code will be executed after loading your module into memory;
 * the exact time is specified in the .plugin file for each module.
 */
void FMobileNativeCodeModule::StartupModule()
{
  // Register settings: `Settings -> Project Settings -> Plugins -> MobileNativeCode`
  if (ISettingsModule* settingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
  {
    UMobileNativeCodeEditorSettings::RegisterEditorSettings(settingsModule);
  }

  // Initialization for Mobile Device
  Initialization();
}

/**
 * This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
 * we call this function before unloading the module.
 */
void FMobileNativeCodeModule::ShutdownModule()
{



}

void FMobileNativeCodeModule::Initialization()
{
#if PLATFORM_ANDROID
  AndroidUtils::Initialization();
#endif


#if PLATFORM_IOS

#endif
}

bool FMobileNativeCodeModule::IsSupported()
{
#if PLATFORM_ANDROID
  return AndroidUtils::isSupportPlatform();
#endif


#if PLATFORM_IOS
  return true;
#endif

  return false;
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMobileNativeCodeModule, MobileNativeCode)