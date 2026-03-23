#include "OD_CraftingBuilding.h"
#include "../SP_Player.h"
#include "OD_RecepieStruct.h"

#include "OD_CraftingRecepie.h"
#include "../Inventory/SP_InventoryComponent.h"

void ACraftingBuilding::UseRecepie(URecepieCraft* recepie)
{
	player->invertoryComponent->UseItemInInventory(recepie->CraftingRecepie->recepie.Input, recepie->CraftingRecepie->recepie.Input.ResorceAmount);
	activeRecepie = recepie;
	recepie->CurrentDuration = recepie->CraftingRecepie->recepie.Duration;
	bIsCrafting = true;
	ActiveCrafts.Add(recepie);
	if (ActiveCrafts.Num() == 0)
	{
		BPStartCraft();
	}
	

}



void ACraftingBuilding::CraftingCycle(float deltatime)
{

	if (ActiveCrafts.Num() > 0)
	{
		for(URecepieCraft* craft : ActiveCrafts)
		{
			if (craft->CurrentDuration > 0)
			{
				craft->CurrentDuration -= deltatime;
				UpdateCraftingDration(craft);
			}
			else
			{
				addItemToInventory(activeRecepie->CraftingRecepie->recepie.Output, activeRecepie->CraftingRecepie->recepie.Output.ResorceAmount);
				craftsToRemove.Add(craft);
				OnCraftingFinished(craft);
			}
		}
	}
	if (craftsToRemove.Num() > 0)
	{
		for (URecepieCraft* craft : craftsToRemove)
		{
			if (ActiveCrafts.Contains(craft))
			{
				ActiveCrafts.Remove(craft);
			}
		}
		craftsToRemove.Empty();

		if (ActiveCrafts.Num()<=0)
		{
			BPFinishCraft();
			bIsCrafting = true;

		}
	}

	//Logic For "Animation"

	//------------------

	
}

void ACraftingBuilding::OnCraftingFinished(URecepieCraft* recepie)
{
	
}

void ACraftingBuilding::UpdateCraftingDration(URecepieCraft* recepie)
{
}



bool ACraftingBuilding::CanCraft(URecepieCraft*& recepie)
{
	bool result = player->invertoryComponent->HasEnoughtOfItemInInventory(recepie->CraftingRecepie->recepie.Input, recepie->CraftingRecepie->recepie.Input.ResorceAmount) && ActiveCrafts.Num() < MaxCraftAmount;
	return result;
}



void ACraftingBuilding::addItemToInventory(FItem item, int UseAmount)
{
	if (BuildingInventory.Contains(item))
	{
		for (int id = 0; id <= BuildingInventory.Num() - 1; id++)
		{

			if (BuildingInventory[id].ItemInfo == item.ItemInfo)
			{
				BuildingInventory[id].ResorceAmount += UseAmount;

			}

		}
	}
	else
	{
		FItem newItem;
		newItem.ItemInfo = item.ItemInfo;
		newItem.ResorceAmount = UseAmount;
		BuildingInventory.Add(newItem);
	}
	
}

void ACraftingBuilding::GivePlayerCraftedItems()
{
	if (BuildingInventory.Num() > 0)
	{
		for (FItem item : BuildingInventory)
		{
			player->invertoryComponent->AddItemInInventory(item, item.ResorceAmount);

		}
		BuildingInventory.Empty();
	}

}
