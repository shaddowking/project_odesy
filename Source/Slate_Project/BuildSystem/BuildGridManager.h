#pragma once

#include "GameFramework/Actor.h"

#include "BuildGridManager.generated.h"


USTRUCT(Blueprintable)
struct FNode
{
	GENERATED_BODY()

	FVector Location;

	bool IsOcupide = false;

	int ID = -1;
};


UCLASS()
class ABuildGridManager : public AActor 
{
	GENERATED_BODY()

public:

	FNode GetClosestNode(FVector Start);

	int GetNodeID(int x, int y, int GridX);

	TArray<FNode> BuildGrid;

	UPROPERTY(EditAnywhere, Category = "Grid")
	int GridSize = 10;
	
	UPROPERTY(EditAnywhere, Category = "Grid")
	float GridZ = 0;

	UPROPERTY(EditAnywhere, Category = "Grid")
	float DistanceBetweenNodes = 1000;

	// Function for visualization
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnDebugCell(FVector pos);

protected:
	void BeginPlay()override;


private:
	void GenerateGrid();

	

};