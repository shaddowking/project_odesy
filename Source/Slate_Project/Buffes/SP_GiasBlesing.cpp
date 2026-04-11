#include "SP_GiasBlesing.h"

float UGiasBlesing::BuffRangeDamageCalculation(ASPCharacter* Owner)
{
    return 0.0f;
}

float UGiasBlesing::BuffMoveSpeedCalculation(ASPCharacter* Owner)
{
    return 0.0f;
}

float UGiasBlesing::BuffRelodeSpeedCalculation(ASPCharacter* Owner)
{
    return 0.0f;
}

float UGiasBlesing::BuffDefenceCalculation(ASPCharacter* Owner)
{
    return 0.5f;
}

void UGiasBlesing::OnBuffDepleted()
{
    Super::OnBuffDepleted();

}
