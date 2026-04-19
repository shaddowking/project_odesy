#pragma once

#include "Components/ActorComponent.h"
#include "UpgradeComponent.generated.h"

class UUpgradeBase;

UCLASS()
class UPlayerUpgradeComponent : public UActorComponent
{
GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<UUpgradeBase*> avalableUpgrades;

	void BeginPlay() override;

	void CreateUpgradeUI();
};