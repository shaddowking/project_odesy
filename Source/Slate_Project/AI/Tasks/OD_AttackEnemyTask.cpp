#include "OD_AttackEnemyTask.h"
#include "../../Enemys/SP_EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../SP_HealthComponent.h"

#include "../OD_AIEnemyController.h"

EBTNodeResult::Type UEnemyAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AEnemyBase* Enemy = GetUnit(OwnerComp);
	AEnemyController* OwningController = GetAIController(OwnerComp);
	AActor* player = Cast<AActor>(BlackboardComp->GetValueAsObject(Target.SelectedKeyName));

	if (FVector::Distance(Enemy->GetActorLocation(),player->GetActorLocation()) > MaxRange)
	{
		BlackboardComp->SetValueAsBool(hasReachedTarget.SelectedKeyName, false);
		return EBTNodeResult::Succeeded;
	}
	
	
	UHealthComponent* healthComponent = player->FindComponentByClass<UHealthComponent>();
	if (healthComponent)
	{
		healthComponent->TakeDamage(Enemy->MelleDamage);
		healthComponent = nullptr;
	}
	BlackboardComp = nullptr;
	Enemy = nullptr;
	OwningController = nullptr;
	player = nullptr;

	return EBTNodeResult::Succeeded;
}
