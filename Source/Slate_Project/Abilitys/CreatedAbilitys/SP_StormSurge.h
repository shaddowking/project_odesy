#pragma once
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"
#include "SP_StormSurge.generated.h"

class ASPVoletileStormProjectile;

UCLASS()
class AStormSurge : public AAbilityBase, public IAbilityInterface {

	GENERATED_BODY()

public:

	TSubclassOf<ASPVoletileStormProjectile> ProjectileRefrence;
	ASPVoletileStormProjectile* projectile;

	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown(float Time) override;
	void CooldownTimer() override;

	// Inherited via AAbilityBase
	FVector GetUltimateSpawnLocation() override;
};