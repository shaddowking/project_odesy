#include "OD_AIEnemyController.h"
#include "../Enemys/SP_EnemyBase.h"

void AEnemyController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	enemy = Cast<AEnemyBase>(aPawn);
	RunBehaviorTree(enemy->BehaviorTree);
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
}
