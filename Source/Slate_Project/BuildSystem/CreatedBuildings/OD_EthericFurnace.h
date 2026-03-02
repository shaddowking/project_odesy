#pragma once

#include "../SP_BuildingBase.h"
#include "OD_EthericFurnace.generated.h"

UCLASS()
class AEthericFurnace : public ABuildingbase
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void ActivateBuilding() override;

	UFUNCTION()
	void DeActivateBuilding() override;

	UFUNCTION()
	void BuildingCreated() override;

	void OnInteract() override;


};