#pragma once

#include "SP_BuildingBase.h"
#include "OD_RecepieStruct.h"
#include "../Inventory/SP_ItemStruct.h"

#include "OD_CraftingBuilding.generated.h"

class URecepieCraft;

UCLASS()
class ACraftingBuilding : public ABuildingbase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	int MaxCraftAmount = 6;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<UCraftingRecepie*> recepieList;

	UPROPERTY(BlueprintReadWrite)
	URecepieCraft* activeRecepie = nullptr;

	virtual void UseRecepie(URecepieCraft* recepie);

	UPROPERTY(BlueprintReadOnly)
	float CurrantCraftDuration = 0;
	float MaxCraftingDuration = 10;
	UPROPERTY(BlueprintReadOnly)
	bool bIsCrafting = false;

	UFUNCTION(BlueprintImplementableEvent)
	void BPStartCraft();

	UFUNCTION(BlueprintImplementableEvent)
	void BPFinishCraft();


	void CraftingCycle(float deltatime);

	virtual void UpdateCraftingDration(URecepieCraft* recepie);

	virtual void OnCraftingFinished(URecepieCraft* recepie);

	virtual bool CanCraft(URecepieCraft*& recepie);


	void addItemToInventory(FItem item, int UseAmount);

	UFUNCTION(BlueprintCallable)
	void GivePlayerCraftedItems();

	UFUNCTION(BlueprintImplementableEvent)
	void AddCraftingUI(URecepieCraft* recepie);

	UPROPERTY(BlueprintReadOnly)
	TArray<URecepieCraft*> ActiveCrafts;
	UPROPERTY(BlueprintReadOnly)
	TArray<URecepieCraft*> craftsToRemove;

private:

	FTimerHandle CraftTimerHandle;

	TArray<FItem> BuildingInventory;

	

};