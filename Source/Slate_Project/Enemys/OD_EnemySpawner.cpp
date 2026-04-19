#include "OD_EnemySpawner.h"
#include "SP_EnemyBase.h"

void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();
    StartEnemySpawning();
}

AEnemySpawner::AEnemySpawner()
{
    SpawnAnker = CreateDefaultSubobject<USceneComponent>("SpawnAnker");
    SpawnAnker->SetupAttachment(RootComponent);
}

void AEnemySpawner::StartEnemySpawning()
{
    if (CreatedEnemys.Num() > 0)
    {
        for(AEnemyBase* enemy : CreatedEnemys)
        {
            enemy->SetActorLocation(GetSpawnPoint());
            enemy->ActivateEnemy();
        }
    }
    else
    {
        AEnemyBase* newEnemy = nullptr;
        for (FEnemyData data : datalist)
        {
            for (size_t i = 0; i < data.SpawnAmount; i++)
            {
                newEnemy = GetWorld()->SpawnActor<AEnemyBase>(data.enemyTemplate, GetSpawnPoint(), FRotator::ZeroRotator);
                CreatedEnemys.Add(newEnemy);
            }
        }
        newEnemy = nullptr;

    }
    

}




FVector AEnemySpawner::GetSpawnPoint()
{
    SpawnPos = FVector::Zero();
    StartPos = (GetActorLocation() + GetActorUpVector() * SpawnHight);
    StartPos.X = StartPos.X + SpawnRange;
    StartPos.Y = StartPos.Y + SpawnRange;

    EndPos = (GetActorLocation() + GetActorUpVector() * SpawnHight);
    EndPos.X = EndPos.X - SpawnRange;
    EndPos.Y = EndPos.Y - SpawnRange;

    SpawnPos.Z = (GetActorLocation() + GetActorUpVector() * SpawnHight).Z;
    SpawnPos.X = FMath::RandRange(EndPos.X, StartPos.X);
    SpawnPos.Y = FMath::RandRange(EndPos.Y, StartPos.Y);


    return SpawnPos;
}



void AEnemySpawner::OnSpawnerActivate()
{
    StartEnemySpawning();
}


