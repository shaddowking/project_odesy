#include "SP_Subclass.h"
#include "../SP_Player.h"
#include "SP_AbilityBase.h"

void ASubclass::InitializeSubclass(ASPCharacter* Player)
{
	Caster = Player;
	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;

	if (UltimateTemplate && !Ultimate)
	{
		Ultimate = GetWorld()->SpawnActor<AAbilityBase>(UltimateTemplate);
		Ultimate->InitialiceAbility(Player);
	}

	if (Ability1Template && !Ability1)
	{
		Ability1 = GetWorld()->SpawnActor<AAbilityBase>(Ability1Template);
		Ability1->InitialiceAbility(Player);
	}

	if (Ability2Template && ! Ability2)
	{
		Ability2 = GetWorld()->SpawnActor<AAbilityBase>(Ability2Template);
		Ability2->InitialiceAbility(Player);
	}
	
	
	
	

	
}
