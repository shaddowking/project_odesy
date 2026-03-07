#pragma once
#include "GameFramework/Actor.h"

#include "OD_BuildingManager.generated.h"

class ABuildingbase;

UCLASS()
class ABuildingManager : public AActor	
{
	GENERATED_BODY()

public:

	TArray<ABuildingbase*> createdbuildings;


	void DeactivateAllBuildings();

	void ActivateAllBuildings();
};