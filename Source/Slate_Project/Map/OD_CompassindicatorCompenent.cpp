#include "OD_CompassindicatorCompenent.h"
#include "../UI/OD_CompassIndicatorUI.h"
#include "../UI/OD_QuestIndicator.h"
#include "../UI/OD_MapMarker.h"
#include "../UI/SP_HUD.h"
#include "../UI/OD_Minimap.h"


void UCompassIndicator::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle creationdealy;

	GetOwner()->GetWorldTimerManager().SetTimer(creationdealy, this, &UCompassIndicator::SetupUI, 0.1, false);

	
	//SetupUI();
}

void UCompassIndicator::DeactivateIndicator()
{
	
	CreatedCIndicator->SetVisibility(ESlateVisibility::Collapsed);
	createdQIndicator->SetVisibility(ESlateVisibility::Collapsed);

}

void UCompassIndicator::ActivateIndicator()
{
	createdQIndicator->SetVisibility(ESlateVisibility::HitTestInvisible);
	CreatedCIndicator->SetVisibility(ESlateVisibility::HitTestInvisible);

}

void UCompassIndicator::SetupUI()
{
	if (GEngine && GEngine->GameViewport)
	{
		target = GetOwner();
		if (bIsCompassInicator)
		{
			if (CompassIconTemplate)
			{
				CreatedCIndicator = CreateWidget<UCompassIndicatorUI>(GetWorld(), CompassIconTemplate);
				if (CreatedCIndicator)
				{
					CreatedCIndicator->AddToViewport();
					CreatedCIndicator->SetupInicator(CompassIcon, target);
				}
			}
		}
		if (bIsWorldInicator)
		{
			if (QuestIconTemplate)
			{
				createdQIndicator = CreateWidget<UQuestIndicator>(GetWorld(), QuestIconTemplate);
				if (createdQIndicator)
				{
					createdQIndicator->AddToViewport();
					createdQIndicator->SetupInicator(CompassIcon, target);
				}
			}
		}
		if (bIsMapInicator)
		{

			ASP_HUD* hud = Cast<ASP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			

			if (hud)
			{
				//hud->SetupMapMarker(CompassIcon,GetOwner(), bHidewhenOffScreen);
				if (hud->Minimap)
				{
					hud->Minimap->addMarker(CompassIcon, target, bHidewhenOffScreen);
				}
			}

			/*
			if (MapIconTemplate)
			{
				CreatedMIndicator = CreateWidget<UMapMarker>(GetWorld(), MapIconTemplate);
				if (CreatedMIndicator)
				{
					CreatedMIndicator->AddToViewport();
					CreatedMIndicator->SetupInicator(CompassIcon, GetOwner());
				}
			}
			*/
		}
		
	}
}




