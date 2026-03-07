#include "SP_BuildSystemComponent.h"
#include "../SP_Player.h"
#include "SP_BuildingBase.h"
#include "../SP_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/SP_InventoryComponent.h"
#include "BuildGridManager.h"
#include "OD_BuildingManager.h"


void UBuildSystemComponent::InitialiceBuildSystem()
{
	//Spawning in the Ghost/Hologram buildings
	if (BuildingList.Num() == 0)
	{
		ABuildingbase* newBuilding = nullptr;
		for (TSubclassOf<ABuildingbase> building : BuildingTemplateList)
		{
			newBuilding = GetWorld()->SpawnActor<ABuildingbase>(building);
			newBuilding->SetGhostMaterial();
			newBuilding->BIsGhost = true;
			newBuilding->DeActivateBuilding();
			BuildingList.Add(newBuilding);

		}
	}
	if (!buildingManager && buildingManagerTemplate)
	{
		buildingManager = GetWorld()->SpawnActor<ABuildingManager>(buildingManagerTemplate);
	}
}

void UBuildSystemComponent::ActivateBuildMode()
{
	//Geting the building grid system

	if (!BuildGridSystem)
	{
		BuildGridSystem = Cast<USPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->BaseGridManager;
	}
	
	
	//Set the current selected to the last selected building or the first building
	SwichBuilding(BuildingID);
}

void UBuildSystemComponent::BuildModeCycle()
{
	
	if (BIsUsingBuildGrid && BuildGridSystem)
	{
		//If using the grid for building
		TargetBuildLocation = BuildGridSystem->GetClosestNode(Player->GetAimPoint(BuildModeRange)).Location;
	}
	else
	{
		// free building
		TargetBuildLocation = Player->GetAimPoint(BuildModeRange);
	}
	if (BuildingGhost)
	{
		BuildingGhost->SetActorLocation(TargetBuildLocation);
	}
}

void UBuildSystemComponent::SwichBuilding(int buildingID)
{
	int MaxbuildingListCount = BuildingList.Num() - 1;
	BuildingID = buildingID;
	if (BuildingID > MaxbuildingListCount)
	{
		BuildingID = MaxbuildingListCount;
	}
	if (BuildingID < 0)
	{
		BuildingID = 0;
	}
	if (BuildingGhost)
	{
		//Hides the old ghost
		BuildingGhost->SetActorHiddenInGame(true);
	}
	CurrentBuilding = BuildingTemplateList[BuildingID];
	BuildingGhost = BuildingList[BuildingID];
	BuildingGhost->SetActorHiddenInGame(false);
	bHasEnoughResorces = Player->invertoryComponent->HasEnoughtOfItemInInventory(BuildingGhost->cost, BuildingGhost->cost.ResorceAmount);

	if (bHasEnoughResorces)
	{
		BuildingGhost->SetGhostMaterial();
	}
	else
	{
		BuildingGhost->SetCantBuildMaterial();
	}
	
}

void UBuildSystemComponent::PlaceBuilding()
{
	bCanBuild = false;
	if (bHasEnoughResorces)
	{
		ABuildingbase* createdBuilding = GetWorld()->SpawnActor<ABuildingbase>(CurrentBuilding, TargetBuildLocation, FRotator::ZeroRotator);
		FNode node = BuildGridSystem->GetClosestNode(TargetBuildLocation);
		BuildGridSystem->BuildGrid[node.ID].IsOcupide = true;
		createdBuilding->BuildingCreated();
		createdBuilding->player = Player;
		createdBuilding->createUI();
		buildingManager->createdbuildings.Add(createdBuilding);
		Player->invertoryComponent->UseItemInInventory(createdBuilding->cost, createdBuilding->cost.ResorceAmount);
	}

	bHasEnoughResorces = Player->invertoryComponent->HasEnoughtOfItemInInventory(BuildingGhost->cost, BuildingGhost->cost.ResorceAmount);
	if (bHasEnoughResorces)
	{
		BuildingGhost->SetGhostMaterial();
	}
	else
	{
		BuildingGhost->SetCantBuildMaterial();
	}
}

void UBuildSystemComponent::DeActivateBuildMode()
{
	BuildingGhost->DeActivateBuilding();
}

bool UBuildSystemComponent::CanBuild()
{
	return false;
}
