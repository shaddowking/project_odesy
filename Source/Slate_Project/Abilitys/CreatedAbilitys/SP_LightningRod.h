#pragma once 
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"

#include "SP_LightningRod.generated.h"

class ALightningRodStrike;

UCLASS()
class ALightningRod : public AAbilityBase , public IAbilityInterface {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALightningRodStrike> LightningTemplate;

	ALightningRodStrike* SpawndLightning = nullptr;

	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown() override;

	virtual void CooldownCompleted() override;
	virtual void UpdateUI(float Value) override;

};