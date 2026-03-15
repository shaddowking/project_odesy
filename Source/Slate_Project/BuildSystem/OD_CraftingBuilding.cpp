#include "OD_CraftingBuilding.h"
#include "../SP_Player.h"
#include "OD_RecepieStruct.h"

#include "../Inventory/SP_InventoryComponent.h"

void ACraftingBuilding::UseRecepie(UCraftingRecepie* recepie)
{
	player->invertoryComponent->UseItemInInventory(recepie->recepie.Input, recepie->recepie.Input.ResorceAmount);
	activeRecepie = recepie;
	StartCrafting(recepie->recepie.Duration);

}

void ACraftingBuilding::StartCrafting(float MaxDuration)
{

	CurrantCraftDuration = MaxDuration;
	MaxCraftingDuration = MaxDuration;
	bIsCrafting = true;
	BPStartCraft();

	GetWorldTimerManager().SetTimer(CraftTimerHandle, this, &ACraftingBuilding::CraftingCycle, 0.01f, false);
}

void ACraftingBuilding::CraftingCycle()
{
	if (CurrantCraftDuration > 0)
	{
		CurrantCraftDuration -= 0.1f;
		UpdateCraftingDration();
		

		GetWorldTimerManager().SetTimer(CraftTimerHandle, this, &ACraftingBuilding::CraftingCycle, 0.1f, false);
	}
	else
	{
		bIsCrafting = false;
		player->invertoryComponent->AddItemInInventory(activeRecepie->recepie.Output, activeRecepie->recepie.Output.ResorceAmount);
		BPFinishCraft();
		OnCraftingFinished();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, "CraftingCompete");

	}
}

void ACraftingBuilding::UpdateCraftingDration()
{
}

void ACraftingBuilding::OnCraftingFinished()
{
}

bool ACraftingBuilding::CanCraft(UCraftingRecepie*& recepie)
{
	bool result = !bIsCrafting && player->invertoryComponent->HasEnoughtOfItemInInventory(recepie->recepie.Input, recepie->recepie.Input.ResorceAmount);
	return result;
}
