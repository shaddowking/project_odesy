#pragma once

#include "Blueprint/UserWidget.h"
#include "OD_BuildingUI.generated.h"

class UCraftingRecepie;
class ACraftingBuilding;

UCLASS()
class UBuildingUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	UCraftingRecepie* CurrentRecepie = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ACraftingBuilding* OwningBuilding = nullptr;

	UFUNCTION(BlueprintCallable)
	void ExitUI();

	void InitializeBuildingUI();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateRecepieUI();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetActiveRecepie(UCraftingRecepie* activerecepie);

	UFUNCTION(BlueprintCallable)
	void ActivateCraft();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimerUI(float Timer);

	UFUNCTION(BlueprintImplementableEvent)
	void CraftingFinished();

	UFUNCTION(BlueprintImplementableEvent)
	void OnStartCraft();
	
	
};