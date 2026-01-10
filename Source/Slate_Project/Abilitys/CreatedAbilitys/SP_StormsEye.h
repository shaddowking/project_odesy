#pragma once
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"
#include "SP_StormsEye.generated.h"

class AStormTurret;

UCLASS()
class AStormsEye : public AAbilityBase, public IAbilityInterface {
	
	GENERATED_BODY()

	

public:

	AStormsEye();

	void Tick(float DeltaTime) override;

	void LanchAbility();


	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown() override;

	virtual void CooldownCompleted() override;

	virtual void UpdateUI(float Value) override;

	virtual void InitialiceAbility(ASPCharacter* player) override;




	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> TargetingTemplate;

	AActor* TargetingActor = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStormTurret> TurretRefrence;

	AStormTurret* CreatedTurret = nullptr;

private:

	FVector TargetLocation;
};