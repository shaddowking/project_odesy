#include "OD_CompassindicatorCompenent.h"
#include "../UI/OD_CompassIndicatorUI.h"
#include "../UI/OD_QuestIndicator.h"



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




