#pragma once
#include "Components/ActorComponent.h"
#include "SP_ItemStruct.h"
#include "SP_InventoryComponent.generated.h"

class UInventoryUI;

UCLASS()
class UInventoryComponent : public UActorComponent 
{

	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FItem> PlayerInventory;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Inventory")
	int InventorySize = 20;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int InventoryX = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int InventoryY = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int NodeOffset = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	FVector2D NodeStartPos;
	

	void CreateInventoryUI();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryUI> UITemplate;

	UPROPERTY()
	UInventoryUI* createdUI = nullptr;

	UFUNCTION(BlueprintCallable)
	int AddItemInInventory(FItem item, int UseAmount);
	UFUNCTION(BlueprintCallable)
	int UseItemInInventory(FItem item, int UseAmount);
	UFUNCTION(BlueprintCallable)
	bool HasEnoughtOfItemInInventory(FItem item, int desierdAmount);

	void OpenInventory();

private: 

	bool HasInventoryEntry(FItem item);

};