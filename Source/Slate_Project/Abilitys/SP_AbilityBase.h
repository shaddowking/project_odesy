#pragma once 

#include "UObject/NameTypes.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"

#include "GameFramework/Actor.h"

#include "AbilityInterface.h"
#include "SP_AbilityBase.generated.h"



class UAbilityDataAsset;
class ASPCharacter;
class ASP_HUD;

UCLASS(abstract)
class AAbilityBase : public AActor {

	GENERATED_BODY()

public:

	bool BIsAbilityActive = false;

	float ActiveCooldown = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAbilityDataAsset* AbilityBaseStates = nullptr;

	virtual void InitialiceAbility(ASPCharacter* player);

	ASPCharacter* Caster = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void spawnDebug(FVector position);

	ASP_HUD* Hud = nullptr;

	float CooldownPercent = 0;

	virtual FVector GetUltimateSpawnLocation();


	virtual void CooldownTimer();

	virtual void CooldownCompleted();

	virtual void UpdateUI(float Value);
	
};