#pragma once
#include "Blueprint/UserWidget.h"
#include "OD_Minimap.generated.h"

UCLASS()
class UMinimap : public UUserWidget
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void addMarker(FSlateBrush icon, AActor* target, bool hidewhenNotVisible);

};