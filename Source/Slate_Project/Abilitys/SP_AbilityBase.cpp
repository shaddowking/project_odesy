#include "SP_AbilityBase.h"

void AAbilityBase::InitialiceAbility(ASPCharacter* player)
{
	Caster = player;
}

FVector AAbilityBase::GetUltimateSpawnLocation() {
	return FVector::ZeroVector;
}
