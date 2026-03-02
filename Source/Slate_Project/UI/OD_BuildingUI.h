#pragma once

#include "Blueprint/UserWidget.h"
#include "OD_BuildingUI.generated.h"

UCLASS()
class UBuildingUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void ExitUI();

	void InitializeBuildingUI();

	
};