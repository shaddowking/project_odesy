#pragma once 
#include "Blueprint/UserWidget.h"
#include "SP_BuffUI.generated.h"


UCLASS()
class UBuffUI : public UUserWidget 
{
GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimerText(float value);

	UFUNCTION(BlueprintCallable)
	FSlateBrush GetBuffIcon()
	{
		return Icon;
	}

	UFUNCTION(BlueprintCallable)
	FString GetBuffName()
	{
		return Name;
	}

	UFUNCTION(BlueprintCallable)
	bool GetTimerVisibility() 
	{
		return isTimerVisible;
	}
	
	FString Name;

	FSlateBrush Icon;

	bool isTimerVisible;
};