#pragma once

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/Class.h"
#include "OD_UpgradeInfoStruct.h"

#include "OD_UpgradeBase.generated.h"

class ASPCharacter;

UCLASS()
class UUpgradeBase : public UObject 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FUpgrade upgradeResorce;

	int UpgradeLevel = 0;

	int CalculateCost();

	virtual void ApplyUpgrade(ASPCharacter* & player);

	

};