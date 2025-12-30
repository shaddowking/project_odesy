#include "SP_Subclass.h"
#include "../SP_Player.h"
#include "SP_AbilityBase.h"

void ASubclass::InitializeSubclass(ASPCharacter* Player)
{
	Caster = Player;
	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;

	
	Ultimate = GetWorld()->SpawnActor<AAbilityBase>(UltimateTemplate);
	
	Ability1 = GetWorld()->SpawnActor<AAbilityBase>(Ability1Template);
	Ability2 = GetWorld()->SpawnActor<AAbilityBase>(Ability2Template);
	Ultimate->InitialiceAbility(Player);
	Ability1->InitialiceAbility(Player);
	Ability2->InitialiceAbility(Player);
	

	
}
