#pragma once
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"
#include "SP_GaiasVenginse.generated.h"

class AGiasTotem;

UCLASS()
class AGiasVeginse : public AAbilityBase, public IAbilityInterface
{
	GENERATED_BODY()
public:

	AGiasVeginse();

	float deltatime = 0;
	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown() override;

	void AbilitySelected() override;

	virtual void CooldownCompleted() override;
	virtual void UpdateUI(float Value) override;

	void Tick(float DeltaTime) override;


	// Inherited via IAbilityInterface

	FVector GetUltimateSpawnLocation() override;

	void OnAbilityPrimaryAttack() override;

	void OnAbilityPrimaryAttackRelease() override;

	void OnAbilitySecendaryAttack() override;

	void OnAbilitySecendaryAttackRealese() override;

	void CreateTotem();

	void MovePlayerToGround();

	UPROPERTY(EditDefaultsOnly)
	float MoveDownSpeed = 3000;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGiasTotem> totamTemplate;

	UPROPERTY()
	AGiasTotem* CreatedTotem = nullptr;
};