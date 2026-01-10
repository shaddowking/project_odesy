#pragma once
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"
#include "SP_StormSurge.generated.h"

class ASPVoletileStormProjectile;

UCLASS()
class AStormSurge : public AAbilityBase, public IAbilityInterface {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASPVoletileStormProjectile> ProjectileRefrence;
	ASPVoletileStormProjectile* projectile;

	void LanchProjectile();

	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown() override;

	virtual void CooldownCompleted() override;

	virtual void UpdateUI(float Value) override;


	

	// Inherited via AAbilityBase
	FVector GetUltimateSpawnLocation() override;
};