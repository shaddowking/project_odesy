#pragma once

#include "GameFramework/Actor.h"

#include "SP_Subclass.generated.h"

class AAbilityBase;
class ASPCharacter;

UCLASS()
class ASubclass : public AActor {
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Template")
	TSubclassOf<AAbilityBase> UltimateTemplate;
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	AAbilityBase* Ultimate;
	UPROPERTY(EditDefaultsOnly, Category = "Template")
	TSubclassOf<AAbilityBase> Ability1Template;
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	AAbilityBase* Ability1;
	UPROPERTY(EditDefaultsOnly, Category = "Template")
	TSubclassOf<AAbilityBase> Ability2Template;
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	AAbilityBase* Ability2;

	UPROPERTY(BlueprintReadOnly)
	ASPCharacter* Caster = nullptr;

	UFUNCTION(BlueprintCallable)
	void InitializeSubclass(ASPCharacter* Player);

	void SubclassSelected();

	UPROPERTY()
	AAbilityBase* ActiveAbility;

};