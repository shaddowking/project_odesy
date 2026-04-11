#include "SP_BuffeBase.h"
#include "Blueprint/UserWidget.h"
#include "../UI/SP_HUD.h"
#include "../UI/SP_BuffUI.h"
#include "../UI/SP_BuffList.h"
#include "../SP_Player.h"
#include "SP_BuffDataAsset.h"

UBuffBase::UBuffBase()
{
}

void UBuffBase::InitializeBuff(ASPCharacter* player, UBuffDataAsset* dataasset)
{
	HasDuration = dataasset->HasDuration;
	MaxDuration = dataasset->Duration;
	Icon = dataasset->BuffBrush;
	Duration = MaxDuration;
	
	if (dataasset->buffUITemplate)
	{
		Player = player;
		if (dataasset->createdUI)
		{
			UI = dataasset->createdUI;
		}
		else
		{
			UI = Player->CreateBuffUI(dataasset->buffUITemplate);
			dataasset->createdUI = UI;
		}
		UI->Icon = Icon;
		UI->Name = dataasset->Name;
		UI->isTimerVisible = dataasset->HasDuration;
		
		Player->hud->buffList->AddBuffUIToList(UI);
		OnBuffBegin();
	}

	
}

void UBuffBase::OnBuffBegin()
{
}


float UBuffBase::BuffRangeDamageCalculation(ASPCharacter* Owner)
{
	return 0.0f;
}

float UBuffBase::BuffDefenceCalculation(ASPCharacter* Owner)
{
	return 1.0f;
}

void UBuffBase::ResetDuration()
{
	Duration = MaxDuration;
}

void UBuffBase::OnBuffDepleted()
{
	Player->hud->buffList->RemoveBuffUIfromList(UI);

}

float UBuffBase::BuffMoveSpeedCalculation(ASPCharacter* Owner)
{
	return 0.0f;
}

float UBuffBase::BuffRelodeSpeedCalculation(ASPCharacter* Owner)
{
	return 0.0f;
}
