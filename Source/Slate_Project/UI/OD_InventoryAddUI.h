#pragma once
#include "Blueprint/UserWidget.h"
#include "../Inventory/SP_ItemStruct.h"
#include "OD_InventoryAddUI.generated.h"

UCLASS()
class UInventoryAdd : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void AddInventoryMessage(FItem item ,int amount);
};