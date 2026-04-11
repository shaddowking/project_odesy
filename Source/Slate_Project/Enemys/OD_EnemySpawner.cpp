#include "OD_EnemySpawner.h"

AEnemySpawner::AEnemySpawner()
{
    SpawnAnker = CreateDefaultSubobject<USceneComponent>("SpawnAnker");
    SpawnAnker->SetupAttachment(RootComponent);
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
