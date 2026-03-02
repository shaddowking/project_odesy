#include "OD_BuildingUI.h"

void UBuildingUI::ExitUI()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBuildingUI::InitializeBuildingUI()
{
}
