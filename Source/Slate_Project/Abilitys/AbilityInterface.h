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

	virtual void ActivateCooldown() = 0;

	virtual void OnAbilityPrimaryAttack() = 0;
	virtual void OnAbilityPrimaryAttackRelease() = 0;


	virtual void OnAbilitySecendaryAttack() = 0;
	virtual void OnAbilitySecendaryAttackRealese() = 0;

};