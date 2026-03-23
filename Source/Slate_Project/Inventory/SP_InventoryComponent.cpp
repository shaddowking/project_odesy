#include "SP_InventoryComponent.h"
#include "SP_ItemStruct.h"
#include "SP_Resorce.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "../UI/OD_InvetoryUI.h"


void UInventoryComponent::CreateInventoryUI()
{
	createdUI = CreateWidget<UInventoryUI>(GetWorld(), UITemplate);
	createdUI->AddToViewport();
	createdUI->SetVisibility(ESlateVisibility::Collapsed);
	createdUI->onwingInventory = this;
	createdUI->CreateInventorySlots();
}

int UInventoryComponent::AddItemInInventory(FItem item, int UseAmount)
{
	if (PlayerInventory.Contains(item))
	{
		
		for (int id = 0; id <= PlayerInventory.Num() - 1; id++)
		{

			if (PlayerInventory[id].ItemInfo == item.ItemInfo)
			{
				PlayerInventory[id].ResorceAmount += UseAmount;
				createdUI->UpdateInventorySlot(PlayerInventory[id].ResorceAmount, PlayerInventory[id]);

			}

		}
	}
	else
	{
		FItem newItem;
		newItem.ItemInfo = item.ItemInfo;
		newItem.ResorceAmount = UseAmount;
		PlayerInventory.Add(newItem);
		createdUI->UpdateInventorySlot(newItem.ResorceAmount, newItem);

	}


	return UseAmount;
}

int UInventoryComponent::UseItemInInventory(FItem item, int UseAmount)
{
	int value = 0;
	for (int id = 0; id <= PlayerInventory.Num() - 1; id++)
	{
		if (PlayerInventory[id].ItemInfo == item.ItemInfo)
		{
			if (PlayerInventory[id].ResorceAmount >= UseAmount)
			{
				PlayerInventory[id].ResorceAmount -= UseAmount;
				value = UseAmount;
				createdUI->UpdateInventorySlot(PlayerInventory[id].ResorceAmount, PlayerInventory[id]);

				break;
			}
			else if (PlayerInventory[id].ResorceAmount < UseAmount)
			{
				value = PlayerInventory[id].ResorceAmount;
				PlayerInventory[id].ResorceAmount = 0;
				createdUI->UpdateInventorySlot(PlayerInventory[id].ResorceAmount, PlayerInventory[id]);

				break;
			}


		}
	}
	return value;
}

bool UInventoryComponent::HasEnoughtOfItemInInventory(FItem item, int desierdAmount)
{
	bool result = false;
	for (FItem Item : PlayerInventory)
	{
		if (Item.ItemInfo == item.ItemInfo && desierdAmount <= Item.ResorceAmount)
		{
			result = true;
			break;
		}
	}
	return result;
}

void UInventoryComponent::OpenInventory()
{
	createdUI->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
}

bool UInventoryComponent::HasInventoryEntry(FItem item)
{
	bool result = false;
	for (int id = 0; id <= PlayerInventory.Num() - 1; id++)
	{

		if (PlayerInventory[id].ItemInfo == item.ItemInfo)
		{
			result = true;
			break;
		}

	}

	return result;
}
