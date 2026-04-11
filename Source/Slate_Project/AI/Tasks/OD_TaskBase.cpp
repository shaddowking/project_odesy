#include "OD_TaskBase.h"
#include "../OD_AIEnemyController.h"
#include "../../Enemys/SP_EnemyBase.h"


UODAITasK::UODAITasK()
{
}

AEnemyController* UODAITasK::GetAIController(const UBehaviorTreeComponent& Owner)
{
	return Cast<AEnemyController>(Owner.GetAIOwner());
}

AEnemyBase* UODAITasK::GetUnit(const UBehaviorTreeComponent& Owner)
{
	AEnemyController* controller = GetAIController(Owner);

	if (!controller)
	{
		return nullptr;
	}

	return Cast<AEnemyBase>(controller->GetPawn());
}