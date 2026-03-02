#include "BuildGridManager.h"
#include <limits>

#include "../SP_GameInstance.h"
#include "Kismet/GameplayStatics.h"



FNode ABuildGridManager::GetClosestNode(FVector AimLocation)
{
	FNode ClosestNode = BuildGrid[0];
	float bestdistance = std::numeric_limits<float>::max();
	float newDist;

	for (FNode& node : BuildGrid) {

		if (node.IsOcupide == false)
		{
			newDist = FVector::Distance(AimLocation, node.Location);
			if (newDist < bestdistance)
			{
				ClosestNode = node;
				bestdistance = newDist;
			}
		}
		
	}

	return ClosestNode;
}

int ABuildGridManager::GetNodeID(int x, int y, int GridX)
{
	return y * GridX + x;
}

void ABuildGridManager::BeginPlay()
{
	Super::BeginPlay();
	//Sets Variable in the game instance so any actor can axes the building grid
	USPGameInstance* GI = Cast<USPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GI->BaseGridManager = this;
	GI = nullptr;
	
	GenerateGrid();
}

void ABuildGridManager::GenerateGrid()
{
	if (BuildGrid.Num() == 0)
	{
		float WorldOfset = (GridSize * DistanceBetweenNodes * 0.5) - (DistanceBetweenNodes * 0.5);
		FVector NewNodePos;
		FNode NewNode;
		FVector ManagerPos = GetActorLocation();

		for (int y = 0; y < GridSize; y++)
		{
			for (int x = 0; x < GridSize; x++)
			{
				NewNodePos = FVector{ ManagerPos.X + (x * DistanceBetweenNodes - WorldOfset),ManagerPos.Y + (y * DistanceBetweenNodes - WorldOfset),ManagerPos.Z };
				SpawnDebugCell(NewNodePos);
				NewNode.Location = NewNodePos;
				NewNode.IsOcupide = false;
				int id = GetNodeID(x, y, GridSize);
				NewNode.ID = id;
				BuildGrid.Add(NewNode);
			}
		}
	}
	

}

