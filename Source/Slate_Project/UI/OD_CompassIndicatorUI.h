#pragma once

#include "Blueprint/UserWidget.h"
#include "OD_CompassIndicatorUI.generated.h"

UCLASS()
class UCompassIndicatorUI : public UUserWidget
{

GENERATED_BODY()


public:


	UPROPERTY(BlueprintReadWrite)
	AActor* TrackingCharacter = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void SetupInicator(FSlateBrush indicator,AActor* tracking);
};