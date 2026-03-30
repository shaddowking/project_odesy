#pragma once
#include "Blueprint/UserWidget.h"
#include "OD_InventoryAddUI.generated.h"

UCLASS()
class UInventoryAdd : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void AddInventoryMessage(int amount);
};