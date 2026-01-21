#pragma once
#include "../SP_AbilityBase.h"
#include "../AbilityInterface.h"
#include "SP_SummenWratch.generated.h"


class ASummonWratch : public AAbilityBase, public IAbilityInterface
{
	GENERATED_BODY()

	// Inherited via IAbilityInterface
	void OnAbilityPressed() override;
	void OnAbilityReleas() override;
	void ActivateCooldown() override;
};