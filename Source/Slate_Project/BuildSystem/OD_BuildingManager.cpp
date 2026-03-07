#include "OD_BuildingManager.h"
#include "SP_BuildingBase.h"

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
