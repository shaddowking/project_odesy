#include "SP_BuffeBase.h"
#include "Blueprint/UserWidget.h"
#include "../UI/SP_HUD.h"
#include "../UI/SP_BuffUI.h"
#include "../UI/SP_BuffList.h"
#include "../SP_Player.h"

UBuffBase::UBuffBase()
{
}

void UBuffBase::InitializeBuff(bool hasduration, float duration, FSlateBrush icon,TSubclassOf<UBuffUI> buffUITemplate, ASPCharacter* player, FString B_name)
{
	HasDuration = hasduration;
	MaxDuration = duration;
	Icon = icon;
	Duration = MaxDuration;
	if (buffUITemplate)
	{
		Player = player;
		UI = Player->CreateBuffUI(buffUITemplate);
		//UI = Cast<UBuffUI>();
		UI->Icon = icon;
		UI->Name = B_name;
		
		Player->hud->buffList->AddBuffUIToList(UI);
		player->UpdateMoveSpeed();
	}

	
}


float UBuffBase::BuffDamageCalculation(ASPCharacter* Owner)
{
	return 0.0f;
}

float UBuffBase::BuffDefenceCalculation(ASPCharacter* Owner)
{
	return 0.0f;
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
