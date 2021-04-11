#pragma once

#include "ToastLengthMessage.generated.h"

UENUM(BlueprintType)
enum class EToastLengthMessage : uint8
{
  /** Short message duration 2 sec  */
  sec2 = 0 UMETA(DisplayName = "Short 2 sec"),

  /** Short message duration 3.5 sec */
  sec3 = 1 UMETA(DisplayName = "Long 3.5 sec"),
};
