#pragma once

#include "../SP_BuildingBase.h"
#include "../OD_RecepieStruct.h"
#include "../OD_CraftingBuilding.h"
#include "OD_EthericFurnace.generated.h"

UCLASS()
class AEthericFurnace : public ACraftingBuilding
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void createUI() override;

	UFUNCTION()
	void ActivateBuilding() override;

	UFUNCTION()
	void DeActivateBuilding() override;

	UFUNCTION()
	void BuildingCreated() override;

	void OnInteract() override;

	void UseRecepie(UCraftingRecepie* recepie) override;

	void UpdateCraftingDration() override;

	void OnCraftingFinished() override;



};