#pragma once

#include "SP_BuffeBase.h"
#include "SP_Amplifide.generated.h"

UCLASS()
class UAmplifide : public UBuffBase 
{
GENERATED_BODY()

public:

	void OnBuffBegin() override;

	 float BuffRangeDamageCalculation(ASPCharacter* Owner) override;

	 float BuffMoveSpeedCalculation(ASPCharacter* Owner)override;

	 float BuffRelodeSpeedCalculation(ASPCharacter* Owner)override;

	 float BuffDefenceCalculation(ASPCharacter* Owner)override;

	 

	 void OnBuffDepleted()override;
};