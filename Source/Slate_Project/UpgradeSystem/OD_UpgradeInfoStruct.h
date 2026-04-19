#pragma once

#include "../Inventory/SP_Resorce.h"

#include "OD_UpgradeInfoStruct.generated.h"


USTRUCT(Blueprintable)
struct FUpgrade
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USP_Resorse* ItemInfo = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int BaseCost = 2;
	  
};