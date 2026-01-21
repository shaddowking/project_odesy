#pragma once
#include "GameFramework/Character.h"
#include "SP_AbilityPlacableCharacter.generated.h"

class ASPCharacter;


UCLASS()
class AAbilityPlacableCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	


	AAbilityPlacableCharacter();

	void InitialicePlaceblecharacter(ASPCharacter* player) { Caster = player; }

	ASPCharacter* Caster = nullptr;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY()
	float duration = 10.0f;

	UPROPERTY(EditAnywhere)
	float Maxduration = 10.0f;

	void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Ability")
	int Damage = 10;

	virtual void Activate(FVector Location);

	virtual void DeActivate();

	UFUNCTION(BlueprintImplementableEvent)
	void BPActivate(FVector Location);

	UFUNCTION(BlueprintImplementableEvent)
	void BPMove(FVector location);

	bool IsActive = false;
};