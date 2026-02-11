#include "SP_HUD.h"
#include "SP_PlayerHud.h"
#include "Widgets/SWeakWidget.h"
#include "Blueprint/UserWidget.h"
#include "SP_BuffList.h"
#include "Engine/Engine.h"

void ASP_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		PlayerHudWidget = SNew(SPlayerHud).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(PHudWidgetContainer, SWeakWidget).PossiblyNullContent(PlayerHudWidget.ToSharedRef()));

		if (buffListTemplate)
		{
			buffList = CreateWidget<UBuffList>(GetWorld(), buffListTemplate);
			if (buffList)
			{
				buffList->AddToViewport();
			}
		}
	}



}

void ASP_HUD::EditorUpdateAmmoTexts(int current, int extra)
{
	PlayerHudWidget->UpdateAmmoText(current, extra);
}
