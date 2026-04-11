#pragma once

#include "OD_TaskBase.h"

#include "OD_MoveEnemyTast.generated.h"

class AEnemyController;
class AEnemyBase;

UCLASS()
class UEnemyMoveTask : public UODAITasK 
{

	GENERATED_BODY()

public: 

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	float AxeptenceRadius;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Target;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector hasReachedTarget;
};
