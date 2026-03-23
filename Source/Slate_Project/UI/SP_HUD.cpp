#include "SP_HUD.h"
#include "SP_PlayerHud.h"
#include "SP_SubclassMenu.h"
#include "Widgets/SWeakWidget.h"
#include "Blueprint/UserWidget.h"
#include "SP_BuffList.h"
#include "OD_CompasUI.h"
#include "Engine/Engine.h"

void ASP_HUD::BeginPlay()
{
	Super::BeginPlay();


	if (GEngine && GEngine->GameViewport)
	{
		
		PlayerHudWidget = SNew(SPlayerHud).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(PHudWidgetContainer, SWeakWidget).PossiblyNullContent(PlayerHudWidget.ToSharedRef()));
		
		//___________________
		
		if (buffListTemplate)
		{
			buffList = CreateWidget<UBuffList>(GetWorld(), buffListTemplate);
			if (buffList)
			{
				buffList->AddToViewport();
			}
		}
		if (CompassTemplate)
		{
			CompassUI = CreateWidget<UCompasUI>(GetWorld(), CompassTemplate);
			if (CompassUI)
			{
				CompassUI->AddToViewport();
			}
		}

		PlayerHudWidget->SetSlateBrushes();
		
	}



}



void ASP_HUD::CreateSubclassMenu(ASPCharacter* player)
{

	if (Player == nullptr)
	{
		Player = player;
	}

	if (GEngine && GEngine->GameViewport)
	{
		SubclassMenu = SNew(SSubclassMenu).OwningHUD(this).OwningCharacter(player);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(PSubclassMenuContainer, SWeakWidget).PossiblyNullContent(SubclassMenu.ToSharedRef()));
		SubclassMenu->SetVisibility(EVisibility::Collapsed);
	}
}

void ASP_HUD::ShowSubclassMenu()
{
	SubclassMenu->SetVisibility(EVisibility::Visible);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

}

void ASP_HUD::HideSubclassMenu()
{
	SubclassMenu->SetVisibility(EVisibility::Collapsed);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
}

void ASP_HUD::EditorUpdateAmmoTexts(int current, int extra)
{
	PlayerHudWidget->UpdateAmmoText(current, extra);
}
