#include "OD_MoveEnemyTast.h"
#include "../../Enemys/SP_EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../OD_AIEnemyController.h"

EBTNodeResult::Type UEnemyMoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AEnemyBase* Enemy = GetUnit(OwnerComp);
	AEnemyController* OwningController = GetAIController(OwnerComp);
	AActor* player = Cast<AActor>(BlackboardComp->GetValueAsObject(Target.SelectedKeyName));

	float dist = FVector::Distance(Enemy->GetActorLocation(), player->GetActorLocation());

	if (dist <= (AxeptenceRadius + AxeptenceRadius * 0.5f))
	{
		BlackboardComp->SetValueAsBool(hasReachedTarget.SelectedKeyName, true);
		return EBTNodeResult::Succeeded;
	}
	

	if (!Enemy)
	{

		return EBTNodeResult::Failed;
	}
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}
	OwningController->MoveToActor(player, AxeptenceRadius);

	BlackboardComp = nullptr;
	Enemy = nullptr;
	OwningController = nullptr;
	player = nullptr;

	return EBTNodeResult::Succeeded;
}
