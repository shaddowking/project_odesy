#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilityInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UAbilityInterface : public UInterface {
	GENERATED_BODY()
};

class IAbilityInterface {
	GENERATED_BODY()

public:

	virtual void OnAbilityPressed() = 0;
	virtual void OnAbilityReleas() = 0;

	virtual void ActivateCooldown(float Time) = 0;
	virtual void CooldownTimer() = 0;
};