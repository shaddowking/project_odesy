#include "SP_AbilityPlacableCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../AI/AbilityPlacableAIController.h"


AAbilityPlacableCharacter::AAbilityPlacableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
}

void AAbilityPlacableCharacter::Spawned()
{
}

void AAbilityPlacableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsActive)
	{
		if (duration <= 0)
		{
			DeActivate();
		}
		else
		{
			duration -= DeltaTime;
		}
	}
}

void AAbilityPlacableCharacter::Activate(FVector Location)
{
	SetActorLocation(Location);
	duration = Maxduration;
	SetActorHiddenInGame(false);
	BPActivate(Location);
	IsActive = true;
	
}

void AAbilityPlacableCharacter::DeActivate()
{
	SetActorHiddenInGame(true);
	IsActive = false;
	BPDeactivate();
	
}

