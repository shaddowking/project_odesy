#pragma once

#include "Components/ActorComponent.h"
#include "SP_BuildSystemComponent.generated.h"

class ABuildingbase;
class ASPCharacter;
class USPGameInstance;
class ABuildGridManager;
class ABuildingManager;




UCLASS(meta = (BlueprintSpawnableComponent))
class UBuildSystemComponent : public UActorComponent
{
GENERATED_BODY()

public:

	UFUNCTION()
	void InitialiceBuildSystem();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABuildingManager> buildingManagerTemplate;

	UPROPERTY()
	ABuildingManager* buildingManager = nullptr;

	bool bCanBuild = true;

	bool bHasEnoughResorces = false;

	UPROPERTY(EditAnywhere)
	bool BIsUsingBuildGrid = true;

	UPROPERTY(EditDefaultsOnly)
	float BuildModeRange = 2000;

	UPROPERTY(EditDefaultsOnly)
	FString BuildLevelName;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ABuildingbase>> BuildingTemplateList;

	ASPCharacter* Player = nullptr;

	void ActivateBuildMode();

	void BuildModeCycle();

	void SwichBuilding(int buildingID);

	void PlaceBuilding();

	void DeActivateBuildMode();

	bool CanBuild();

private:

	FActorSpawnParameters BuildParams;

	UPROPERTY()
	ULevelStreaming* BuildLevel = nullptr;

	UPROPERTY()
	ULevel* selectedLevel = nullptr;

	int BuildingID = 0;

	UPROPERTY()
	ABuildGridManager* BuildGridSystem = nullptr;

	TArray<ABuildingbase*> BuildingList;

	UPROPERTY()
	ABuildingbase* BuildingGhost = nullptr;

	UPROPERTY()
	TSubclassOf<ABuildingbase> CurrentBuilding;

	FVector TargetBuildLocation;

	UPROPERTY()
	ABuildingbase* createdBuilding = nullptr;


};