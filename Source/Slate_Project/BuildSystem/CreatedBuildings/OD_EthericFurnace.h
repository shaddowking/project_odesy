#pragma once

#include "../SP_BuildingBase.h"
#include "../OD_RecepieStruct.h"
#include "../OD_CraftingBuilding.h"
#include "OD_EthericFurnace.generated.h"

class UCraftingRecepie;

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


	void UpdateCraftingDration(URecepieCraft* recepie) override;

	void OnCraftingFinished(URecepieCraft* recepie) override;

	void UseRecepie(URecepieCraft* recepie) override;



};