#pragma once 
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"

#include "SP_LightningRod.generated.h"

class ALightningRodStrike;
class UBuffBase;

UCLASS()
class ALightningRod : public AAbilityBase , public IAbilityInterface {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALightningRodStrike> LightningTemplate;

	UPROPERTY()
	ALightningRodStrike* SpawndLightning = nullptr;

	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown() override;

	void AbilitySelected() override;



	virtual void CooldownCompleted() override;
	virtual void UpdateUI(float Value) override;


	// Inherited via IAbilityInterface
	void OnAbilityPrimaryAttack() override;

	void OnAbilityPrimaryAttackRelease() override;

	void OnAbilitySecendaryAttack() override;

	void OnAbilitySecendaryAttackRealese() override;


protected:

	UPROPERTY()
	UBuffBase* newBuff = nullptr;
};