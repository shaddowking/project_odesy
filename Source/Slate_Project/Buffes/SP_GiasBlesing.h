#pragma once


#include "SP_BuffeBase.h"

#include "SP_GiasBlesing.generated.h"

UCLASS()
class UGiasBlesing : public UBuffBase
{
	GENERATED_BODY()

public:

	float BuffRangeDamageCalculation(ASPCharacter* Owner) override;

	float BuffMoveSpeedCalculation(ASPCharacter* Owner)override;

	float BuffRelodeSpeedCalculation(ASPCharacter* Owner)override;

	float BuffDefenceCalculation(ASPCharacter* Owner)override;



	void OnBuffDepleted()override;
};