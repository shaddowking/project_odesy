#pragma once

#include "Blueprint/UserWidget.h"
#include "OD_BuildingUI.generated.h"

class UCraftingRecepie;
class ACraftingBuilding;
class UCraftUI;
class URecepieCraft;
UCLASS()
class UBuildingUI : public UUserWidget
{
	GENERATED_BODY()

public:

	
	UPROPERTY(BlueprintReadWrite)
	URecepieCraft* CurrentRecepie = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ACraftingBuilding* OwningBuilding = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TArray<UCraftUI*> CraftUIList;

	UFUNCTION(BlueprintCallable)
	void ExitUI();

	void InitializeBuildingUI();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateRecepieUI();

	UFUNCTION(BlueprintCallable)
	void SetActiveRecepie(UCraftingRecepie* activerecepie);

	UFUNCTION(BlueprintCallable)
	void ActivateCraft();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimerUI(float Timer, UCraftUI* CUI);

	UFUNCTION(BlueprintImplementableEvent)
	void CraftingFinished(UCraftUI* CUI);

	UFUNCTION(BlueprintImplementableEvent)
	void OnStartCraft(UCraftUI* CUI);

	UFUNCTION(BlueprintCallable)
	UCraftUI* GetNextCraftUI();
	
	
};