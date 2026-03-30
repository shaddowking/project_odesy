#include "OD_CompassindicatorCompenent.h"
#include "../UI/OD_CompassIndicatorUI.h"
#include "../UI/OD_QuestIndicator.h"



void UCompassIndicator::BeginPlay()
{
	Super::BeginPlay();
	SetupUI();
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
		if (bIsCompassInicator)
		{
			if (CompassIconTemplate)
			{
				CreatedCIndicator = CreateWidget<UCompassIndicatorUI>(GetWorld(), CompassIconTemplate);
				if (CreatedCIndicator)
				{
					CreatedCIndicator->AddToViewport();
					CreatedCIndicator->SetupInicator(CompassIcon, GetOwner());
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
					createdQIndicator->SetupInicator(CompassIcon, GetOwner());
				}
			}
		}
		if (bIsMapInicator)
		{

		}
		
	}
}




