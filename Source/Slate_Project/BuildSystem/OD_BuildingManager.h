#pragma once
#include "GameFramework/Actor.h"

#include "OD_BuildingManager.generated.h"

class ABuildingbase;
class ACraftingBuilding;
UCLASS()
class ABuildingManager : public AActor	
{
	GENERATED_BODY()

public:

	ABuildingManager();



	TArray<ABuildingbase*> createdbuildings;

	void Tick(float DeltaTime) override;



	void DeactivateAllBuildings();

	void ActivateAllBuildings();

private:

	ACraftingBuilding* CurrentCraftBuild = nullptr;
};