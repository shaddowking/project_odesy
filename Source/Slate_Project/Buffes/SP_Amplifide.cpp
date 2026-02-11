#include "SP_Amplifide.h"

float UAmplifide::BuffDamageCalculation(ASPCharacter*& Owner)
{
	return 10;
}

float UAmplifide::BuffMoveSpeedCalculation(ASPCharacter*& Owner)
{
	return 0.0f;
}

float UAmplifide::BuffRelodeSpeedCalculation(ASPCharacter*& Owner)
{
	return 0.0f;
}

float UAmplifide::BuffDefenceCalculation(ASPCharacter*& Owner)
{
	return 0.0f;
}

void UAmplifide::OnBuffDepleted()
{
	Super::OnBuffDepleted();
}
