#pragma once

#include "BehaviorTree/BTTaskNode.h"


#include "OD_TaskBase.generated.h"

class AEnemyController;
class AEnemyBase;

UCLASS()
class UODAITasK : public UBTTaskNode
{

	GENERATED_BODY()

public:

	UODAITasK();

	static AEnemyController* GetAIController(const UBehaviorTreeComponent& Owner);
	static AEnemyBase* GetUnit(const UBehaviorTreeComponent& Owner);

};