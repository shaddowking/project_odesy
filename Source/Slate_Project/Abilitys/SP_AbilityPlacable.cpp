#include "SP_AbilityPlacable.h"

AAbilityPlacable::AAbilityPlacable()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

}

void AAbilityPlacable::Activate(FVector Location)
{
	SetActorLocation(Location);
	duration = Maxduration;
	SetActorHiddenInGame(false);
	IsActive = true;
}
