#pragma once

#include "OD_TaskBase.h"

#include "OD_AttackEnemyTask.generated.h"

UCLASS()
class UEnemyAttackTask : public UODAITasK
{
	GENERATED_BODY()

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	float MaxRange = 100;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Target;	
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector hasReachedTarget;


};