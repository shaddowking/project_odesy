#pragma once
#include "Blueprint/UserWidget.h"

#include "OD_CompasUI.generated.h"

UCLASS()
class UCompasUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCompasRotation(float rotation);
};