#pragma once
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"
#include "SP_SummenWratch.generated.h"

class AWratch;

UCLASS()
class ASummonWratch : public AAbilityBase, public IAbilityInterface
{
	GENERATED_BODY()

public:
	ASummonWratch();

	void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> TargetingTemplate;


	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown() override;

	void AbilitySelected() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWratch> WratchTemplate;

	AWratch* CreatedWratch = nullptr;

	virtual void CooldownCompleted() override;

	virtual void UpdateUI(float Value) override;

	virtual void InitialiceAbility(ASPCharacter* player) override;

	

	FVector TargetLocation;

	AActor* TargetingActor = nullptr;



};