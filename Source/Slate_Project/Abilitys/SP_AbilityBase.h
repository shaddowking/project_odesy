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

UCLASS()
class AAbilityBase : public AActor {
	GENERATED_BODY()

public:

	float ActiveCooldown = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAbilityDataAsset* AbilityBaseStates = nullptr;

	void InitialiceAbility(ASPCharacter* player) { Caster = player; }

	ASPCharacter* Caster = nullptr;


	virtual FVector GetUltimateSpawnLocation() = 0;
	
};