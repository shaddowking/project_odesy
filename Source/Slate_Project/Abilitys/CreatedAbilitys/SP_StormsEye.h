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


	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown(float Time) override;
	void CooldownTimer() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> TargetingTemplate;

	AActor* TargetingActor = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStormTurret> TurretRefrence;

	AStormTurret* CreatedTurret = nullptr;

private:

	FVector TargetLocation;
};