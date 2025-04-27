#include "MobileNativeCodeEditorSettings.h"

#define LOCTEXT_NAMESPACE "FMobileNativeCodeModule"

UMobileNativeCodeEditorSettings::UMobileNativeCodeEditorSettings(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

//----------------------------------------------------------------------
void UMobileNativeCodeEditorSettings::RegisterEditorSettings(ISettingsModule* settingsModule)
{
  settingsModule->RegisterSettings("Project", "Plugins", "MobileNativeCode",
    LOCTEXT("RuntimeSettingsName", "MobileNativeCode"),
    LOCTEXT("RuntimeSettingsDescription", "Configure bundle(plugin)"),
    GetMutableDefault<UMobileNativeCodeEditorSettings>());
}

#undef LOCTEXT_NAMESPACE