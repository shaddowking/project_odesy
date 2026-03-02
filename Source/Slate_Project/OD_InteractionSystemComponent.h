#pragma once

#include "Components/ActorComponent.h"
#include "OD_InteractionSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractSigneture);


UCLASS(meta = (BlueprintSpawnableComponent))
class UInteractionComponent : public UActorComponent 
{
	GENERATED_BODY()

public:

	void Interact()
	{
		OnInteracted.Broadcast();
	}

	FInteractSigneture OnInteracted;
};