#include "OD_QuestIndicator.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void UQuestIndicator::UpdateWidgetClampValues(FVector2D ViewportSize, FVector2D IconSize,float ViewportScale)
{
	if (SavedViewportSize != ViewportSize)
	{
		SavedViewportSize = ViewportSize;
		ClampMin = IconSize / 2;
		ClampMax = SavedViewportSize / ViewportScale - ClampMin;
	}
}

bool UQuestIndicator::IsTargetLocationWithinScreenClamp(FVector Worldpos, float ViewportScale)
{

	if (UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), Worldpos, widgetPos, true))
	{
		ScreenPosition = widgetPos / ViewportScale;
		if (UKismetMathLibrary::InRange_FloatFloat(ScreenPosition.X,ClampMin.X,ClampMax.X))
		{
			if (UKismetMathLibrary::InRange_FloatFloat(ScreenPosition.Y, ClampMin.Y, ClampMax.Y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		
	}
	else
	{
		return false;
	}
}

void UQuestIndicator::UpdateMidpointPosandDirection(float ViewportScale)
{
	
	 UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), SavedViewportSize / 2, MiddlePorint, worldDirection);
	 ObjectDirection = UKismetMathLibrary::GetDirectionUnitVector(MiddlePorint, TargetLocation);
	 MidPointTowardsObject = MiddlePorint + (ObjectDirection * Acuracy);

	 ScreenMiddle2D = (SavedViewportSize / ViewportScale) / 2;
	 RunAndRise = ScreenMiddle2D - ScreenPosition;
	 LineLengh = UKismetMathLibrary::GetMin2D(UKismetMathLibrary::GetAbs2D((ScreenMiddle2D - ClampMin) / RunAndRise));

	 ScreenPosition = ScreenMiddle2D - RunAndRise * LineLengh;

	 UpdateWidgetLocation(false);
}

