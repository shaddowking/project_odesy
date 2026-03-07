#include "OD_BuildingUI.h"
#include "../SP_Player.h"
#include "../Inventory/SP_InventoryComponent.h"
#include "../BuildSystem/OD_RecepieStruct.h"
#include "../BuildSystem/OD_CraftingBuilding.h"

void UBuildingUI::ExitUI()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBuildingUI::InitializeBuildingUI()
{
	

}

void UBuildingUI::ActivateCraft()
{
	if (OwningBuilding && CurrentRecepie && OwningBuilding->CanCraft(CurrentRecepie))
	{
		OnStartCraft();
		OwningBuilding->UseRecepie(CurrentRecepie);
	}
}
