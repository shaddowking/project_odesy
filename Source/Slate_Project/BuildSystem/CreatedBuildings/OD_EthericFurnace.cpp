#include "OD_EthericFurnace.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "../../SP_Player.h"
#include "../../Inventory/SP_InventoryComponent.h"
#include "../SP_BuildSystemComponent.h"
#include "../../UI/OD_BuildingUI.h"

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

void AEthericFurnace::UseRecepie(UCraftingRecepie* recepie)
{
	Super::UseRecepie(recepie);
}

void AEthericFurnace::UpdateCraftingDration()
{
	createdUI->UpdateTimerUI(CurrantCraftDuration);
}

void AEthericFurnace::OnCraftingFinished()
{
	createdUI->CraftingFinished();
}


