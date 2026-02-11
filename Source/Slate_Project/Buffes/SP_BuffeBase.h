#pragma once
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/Class.h"

#include "SP_BuffeBase.generated.h"

class ASPCharacter;
class ASP_HUD;
class UBuffUI;
UCLASS()
class UBuffBase : public UObject 
{
	GENERATED_BODY()

public:
	UBuffBase();

	void InitializeBuff(bool hasduration, float duration, FSlateBrush icon, TSubclassOf<UBuffUI> buffUITemplate,ASPCharacter* player, FString B_name);
	


	virtual float BuffDamageCalculation(ASPCharacter* Owner);

	virtual float BuffMoveSpeedCalculation(ASPCharacter* Owner);

	virtual float BuffRelodeSpeedCalculation(ASPCharacter* Owner);

	virtual float BuffDefenceCalculation(ASPCharacter* Owner);

	virtual void ResetDuration();

	virtual void OnBuffDepleted();

	bool HasDuration = true;

	UPROPERTY(EditAnywhere)
	FSlateBrush Icon;

	float MaxDuration = 10;

	float Duration = 0;

	UBuffUI* UI = nullptr;
	ASP_HUD* hud = nullptr;

	ASPCharacter* Player = nullptr;

	UUserWidget* test = nullptr;


private:

	


};