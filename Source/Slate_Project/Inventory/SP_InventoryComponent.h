#pragma once
#include "Components/ActorComponent.h"
#include "SP_ItemStruct.h"
#include "SP_InventoryComponent.generated.h"

UCLASS()
class UInventoryComponent : public UActorComponent 
{

	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere)
	TArray<FItem> PlayerInventory;


	int AddItemInInventory(FItem item, int UseAmount);
	int UseItemInInventory(FItem item, int UseAmount);
	bool HasEnoughtOfItemInInventory(FItem item, int desierdAmount);

private: 

	bool HasInventoryEntry(FItem item);

};