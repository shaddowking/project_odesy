#include "OD_InvetoryUI.h"

void UInventoryUI::ExitInventory()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Collapsed);
}

