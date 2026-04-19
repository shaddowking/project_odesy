#pragma once
#include "GameFramework/Actor.h"
#include "../Inventory/SP_ItemStruct.h"
#include "OD_ExploreManager.generated.h"

class AOreBase;
class AItemPickup;
class AEnemySpawner;

UCLASS()
class AExploreManager : public AActor
{

	GENERATED_BODY()

public:

	void BeginPlay()override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AOreBase*> createdOreList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AEnemySpawner*> EnemySpawnerList;

	TArray<AItemPickup*> pickupPool;

	
	AItemPickup* GetPickup(FItem desierdPickup, AOreBase* currentOre);

	AItemPickup* AddNewpickup(TSubclassOf<AItemPickup> newpickup, FVector position);

	void Activate();

	void Deactivate();

private:

	UPROPERTY()
	AItemPickup* curerntPickup = nullptr;


	UPROPERTY()
	AItemPickup* NewPickup = nullptr;
};