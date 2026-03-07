#pragma once
#include "Blueprint/UserWidget.h"
#include "../Inventory/SP_ItemStruct.h"
#include "OD_InvetoryUI.generated.h"

class UInventoryComponent;

UCLASS()
class UInventoryUI : public	UUserWidget
{
GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	UInventoryComponent* onwingInventory = nullptr;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void CreateInventorySlots();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateInventorySlot(int amountToAdd, FItem item);

	UFUNCTION(BlueprintCallable)
	void ExitInventory();

};