 #pragma once

#include "Blueprint/UserWidget.h"

#include "OD_MapMarker.generated.h"

class UMinimap;

UCLASS()
class UMapMarker : public UUserWidget
{

	GENERATED_BODY()

public:



	UPROPERTY(BlueprintReadWrite)
	AActor* TrackingActor = nullptr;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetupInicator(FSlateBrush indicator, AActor* tracking);

	UPROPERTY(EditAnywhere,BlueprintReadWrite )
	bool IsActive = false;

};