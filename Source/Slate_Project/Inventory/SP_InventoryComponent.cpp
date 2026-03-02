#include "SP_InventoryComponent.h"
#include "SP_ItemStruct.h"
#include "SP_Resorce.h"



int UInventoryComponent::AddItemInInventory(FItem item, int UseAmount)
{
	if (HasInventoryEntry(item))
	{
		
		for (int id = 0; id <= PlayerInventory.Num() - 1; id++)
		{

			if (PlayerInventory[id].ItemInfo == item.ItemInfo)
			{
				PlayerInventory[id].ResorceAmount += UseAmount;
			}

		}
	}
	else
	{
		FItem newItem;
		newItem.ItemInfo = item.ItemInfo;
		newItem.ResorceAmount = UseAmount;
		PlayerInventory.Add(newItem);
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
				break;
			}
			else if (PlayerInventory[id].ResorceAmount < UseAmount)
			{
				value = PlayerInventory[id].ResorceAmount;
				PlayerInventory[id].ResorceAmount = 0;
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
