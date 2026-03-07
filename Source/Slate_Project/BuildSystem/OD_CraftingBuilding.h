#pragma once

#include "SP_BuildingBase.h"
#include "OD_RecepieStruct.h"

#include "OD_CraftingBuilding.generated.h"

UCLASS()
class ACraftingBuilding : public ABuildingbase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<UCraftingRecepie*> recepieList;

	UPROPERTY(BlueprintReadWrite)
	UCraftingRecepie* activeRecepie = nullptr;

	virtual void UseRecepie(UCraftingRecepie* recepie);
	UPROPERTY(BlueprintReadOnly)
	float CurrantCraftDuration = 0;
	float MaxCraftingDuration = 10;
	UPROPERTY(BlueprintReadOnly)
	bool bIsCrafting = false;

	UFUNCTION(BlueprintImplementableEvent)
	void BPStartCraft();

	UFUNCTION(BlueprintImplementableEvent)
	void BPFinishCraft();

	void StartCrafting(float MaxDuration);

	void CraftingCycle();

	virtual void UpdateCraftingDration();

	virtual void OnCraftingFinished();

	virtual bool CanCraft(UCraftingRecepie*& recepie);
};