#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/PlayerController.h"

#include "OD_AIEnemyController.generated.h"

class AEnemyBase;

UCLASS()
class AEnemyController : public AAIController 
{
	GENERATED_BODY()

public:

public:

	UPROPERTY(BlueprintReadWrite)
	AEnemyBase* enemy = nullptr;

private:

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;


};