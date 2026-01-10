#include "SP_AbilityPlacable.h"

AAbilityPlacable::AAbilityPlacable()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

}

void AAbilityPlacable::Tick(float DeltaTime)
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

void AAbilityPlacable::Activate(FVector Location)
{
	SetActorLocation(Location);
	duration = Maxduration;
	SetActorHiddenInGame(false);
	BPActivate(Location);

	IsActive = true;
}

void AAbilityPlacable::DeActivate()
{
	SetActorHiddenInGame(true);
	IsActive = false;
}
