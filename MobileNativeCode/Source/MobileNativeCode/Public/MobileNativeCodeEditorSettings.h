#pragma once

#include "Developer/Settings/Public/ISettingsModule.h"
#include "MobileNativeCodeEditorSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UMobileNativeCodeEditorSettings : public UObject
{
  GENERATED_BODY()

public:
  UMobileNativeCodeEditorSettings(const FObjectInitializer& ObjectInitializer);  

  static void RegisterEditorSettings(ISettingsModule* settingsModule);

};
