#pragma once
#include "GameFramework/Actor.h"
#include "SP_AbilityPlacable.generated.h"

class ASPCharacter;

UCLASS()
class AAbilityPlacable : public AActor {
	GENERATED_BODY()

public:
	
	void InitialicePlaceble(ASPCharacter*& player) { Caster = player; }


	AAbilityPlacable();

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
	void BPDeactivate();

	UFUNCTION(BlueprintImplementableEvent)
	void BPMove(FVector location);

	bool IsActive = false;
};