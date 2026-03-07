#pragma once
#include "Blueprint/UserWidget.h"
#include "../Inventory/SP_ItemStruct.h"

#include "OD_ItemSlot.generated.h"

UCLASS()
class UItemSlot : public UUserWidget
{
GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	int SlotAmount= 0;
	UPROPERTY(BlueprintReadWrite)
	FItem item;

};