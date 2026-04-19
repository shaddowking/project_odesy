#pragma once

#include "GameFramework/Actor.h"

#include "OD_EnemySpawner.generated.h"

class AEnemyBase;

USTRUCT(Blueprintable)
struct FEnemyData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AEnemyBase> enemyTemplate;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int SpawnAmount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnDelay = 10;
	
};


UCLASS()
class AEnemySpawner : public AActor
{
GENERATED_BODY()


public: 

	void BeginPlay() override;

	AEnemySpawner();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USceneComponent* SpawnAnker = nullptr;

	UFUNCTION(BlueprintCallable)
    void StartEnemySpawning();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FEnemyData> datalist;
	UPROPERTY(BlueprintReadOnly)
	TArray<AEnemyBase*> CreatedEnemys;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float SpawnRange = 500;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnHight = 300;

	UFUNCTION(BlueprintCallable)
	FVector GetSpawnPoint();

	UFUNCTION(BlueprintImplementableEvent)
	void DeactivateSpawner();

	UFUNCTION()
	void OnSpawnerActivate();

private:

	FVector StartPos;
	FVector EndPos;
	FVector SpawnPos;
};