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
	float SpawnAmount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnDelay = 10;
	
};


UCLASS()
class AEnemySpawner : public AActor
{
GENERATED_BODY()


public: 

	AEnemySpawner();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USceneComponent* SpawnAnker = nullptr;

    UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
    void StartSpawning();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FEnemyData> datalist;

	UPROPERTY(EditAnywhere)
	float SpawnRange = 500;

	UPROPERTY(EditAnywhere)
	float SpawnHight = 300;

	UFUNCTION(BlueprintCallable)
	FVector GetSpawnPoint();

private:

	FVector StartPos;
	FVector EndPos;
	FVector SpawnPos;
};