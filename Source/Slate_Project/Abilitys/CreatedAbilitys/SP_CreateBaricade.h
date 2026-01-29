#pragma once 
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"

#include "SP_CreateBaricade.generated.h"

class AEarthBaricade;

UCLASS()
class AEarthBaricadeAbility: public AAbilityBase, public IAbilityInterface
{
	GENERATED_BODY()

public:

	AEarthBaricadeAbility();

	void Tick(float DeltaTime) override;

	void LaunchAbility();


	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown() override;

	void AbilitySelected() override;

	virtual void CooldownCompleted() override;

	virtual void UpdateUI(float Value) override;

	virtual void InitialiceAbility(ASPCharacter* player) override;


private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> BaricadeTargetingTemplate;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	AActor* BaricadeTargeting = nullptr;
	FVector TargetLocation;
	FVector playerDirection;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEarthBaricade> placableTemplate;
	AEarthBaricade* createdBaricade = nullptr;

};