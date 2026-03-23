#include "OD_EthericFurnace.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "../../SP_Player.h"
#include "../../Inventory/SP_InventoryComponent.h"
#include "../SP_BuildSystemComponent.h"
#include "../../UI/OD_BuildingUI.h"
#include "../../UI/OD_CraftUI.h"
#include "../OD_CraftingRecepie.h"

void AEthericFurnace::createUI()
{
	if (BuildingUITemplate && BIsGhost == false)
	{
		createdUI = CreateWidget<UBuildingUI>(GetWorld(), BuildingUITemplate);
		createdUI->AddToViewport();
		createdUI->SetVisibility(ESlateVisibility::Collapsed);
		createdUI->OwningBuilding = this;
		createdUI->CreateRecepieUI();
	}
}

void AEthericFurnace::ActivateBuilding()
{
	Super::ActivateBuilding();
}

void AEthericFurnace::DeActivateBuilding()
{
	Super::DeActivateBuilding();
}

void AEthericFurnace::BuildingCreated()
{
	Super::BuildingCreated(); 
}

void AEthericFurnace::OnInteract()
{
	Super::OnInteract();
}



void AEthericFurnace::UpdateCraftingDration(URecepieCraft* recepie)
{
	recepie->owningUI->UpdateCraftTimer(recepie->CurrentDuration);
}

void AEthericFurnace::OnCraftingFinished(URecepieCraft* recepie)
{
	recepie->owningUI->bIsTaken = false;
	createdUI->CraftingFinished(recepie->owningUI);
}

void AEthericFurnace::UseRecepie(URecepieCraft* recepie)
{
	UCraftUI* newUI = createdUI->GetNextCraftUI();
	if (newUI)
	{
		recepie->owningUI = newUI;
		recepie->owningUI->ApplyCraftingRecepie(recepie);
		recepie->owningUI->bIsTaken = true;
		newUI = nullptr;
	}

	// Temp
	player->invertoryComponent->UseItemInInventory(recepie->CraftingRecepie->recepie.Input, recepie->CraftingRecepie->recepie.Input.ResorceAmount);
	activeRecepie = recepie;
	recepie->CurrentDuration = recepie->CraftingRecepie->recepie.Duration;
	BPStartCraft();
	bIsCrafting = true;
	ActiveCrafts.Add(recepie);

	//___________
	//Super::UseRecepie(recepie);

	createdUI->OnStartCraft(recepie->owningUI);
	//UpdateUI
	
}


