#pragma once
#include "Blueprint/UserWidget.h"
#include "OD_CraftUI.generated.h"

class UCraftingRecepie;
class URecepieCraft;

UCLASS()
class UCraftUI : public UUserWidget 
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void ApplyCraftingRecepie(URecepieCraft* recepie);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void UpdateCraftTimer(float Value);

	UPROPERTY(BlueprintReadWrite)
	bool bIsTaken = false;
};