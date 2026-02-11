#include "SP_Amplifide.h"
#include "../SP_Player.h"

float UAmplifide::BuffDamageCalculation(ASPCharacter* Owner)
{
	return 10;
}

float UAmplifide::BuffMoveSpeedCalculation(ASPCharacter* Owner)
{
	return Owner->currentMoveSpeed * 0.5;
}

float UAmplifide::BuffRelodeSpeedCalculation(ASPCharacter* Owner)
{
	return 0.0f;
}

float UAmplifide::BuffDefenceCalculation(ASPCharacter* Owner)
{
	return 0.0f;
}

void UAmplifide::OnBuffDepleted()
{
	Super::OnBuffDepleted();
	Player->UpdateMoveSpeed();


}
