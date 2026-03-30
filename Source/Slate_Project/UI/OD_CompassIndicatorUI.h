#pragma once

#include "Blueprint/UserWidget.h"
#include "OD_CompassIndicatorUI.generated.h"

UCLASS()
class UCompassIndicatorUI : public UUserWidget
{

GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxRange = 1000;

	UPROPERTY(BlueprintReadWrite)
	AActor* TrackingCharacter = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void SetupInicator(FSlateBrush indicator,AActor* tracking);
};