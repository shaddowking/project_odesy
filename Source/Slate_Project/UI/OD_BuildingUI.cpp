#include "OD_BuildingUI.h"
#include "../SP_Player.h"
#include "../Inventory/SP_InventoryComponent.h"
#include "../BuildSystem/OD_RecepieStruct.h"
#include "../BuildSystem/OD_CraftingBuilding.h"
#include "../UI/OD_CraftUI.h"
#include "../BuildSystem/OD_CraftingRecepie.h"
void UBuildingUI::ExitUI()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBuildingUI::InitializeBuildingUI()
{
	

}

void UBuildingUI::SetActiveRecepie(UCraftingRecepie* activerecepie)
{
	URecepieCraft* newcraft = NewObject<URecepieCraft>(URecepieCraft::StaticClass());
	newcraft->CraftingRecepie = activerecepie;
	CurrentRecepie = newcraft;
	OwningBuilding->activeRecepie = CurrentRecepie;
	//newcraft = nullptr;
}

void UBuildingUI::ActivateCraft()
{
	if (OwningBuilding && CurrentRecepie && OwningBuilding->CanCraft(CurrentRecepie))
	{
		URecepieCraft* newRecepie = NewObject<URecepieCraft>(CurrentRecepie);
		newRecepie->CraftingRecepie = CurrentRecepie->CraftingRecepie;
		OwningBuilding->UseRecepie(newRecepie);

		newRecepie = nullptr;
	}
}

UCraftUI* UBuildingUI::GetNextCraftUI()
{

	for (UCraftUI* CUI : CraftUIList) 
	{
		if (!CUI->bIsTaken)
		{
			return CUI;
		}
	}
	return nullptr;
}
