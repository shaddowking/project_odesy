#include "OD_BuildingManager.h"
#include "SP_BuildingBase.h"
#include "OD_CraftingBuilding.h"

ABuildingManager::ABuildingManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (ABuildingbase* building : createdbuildings)
	{
		CurrentCraftBuild = Cast<ACraftingBuilding>(building);
		if (CurrentCraftBuild)
		{
			CurrentCraftBuild->CraftingCycle(DeltaTime);
			CurrentCraftBuild = nullptr;
		}
	}
}

void ABuildingManager::DeactivateAllBuildings()
{
	for(ABuildingbase* building : createdbuildings)
	{
		building->DeActivateBuilding();
	}
}

void ABuildingManager::ActivateAllBuildings()
{
	for (ABuildingbase* building : createdbuildings)
	{
		building->ActivateBuilding();
	}
}
