#pragma once
#include "Blueprint/UserWidget.h"
#include "../BuildSystem/OD_RecepieStruct.h"
#include "OD_RecepieUI.generated.h"

class UBuildingUI;

UCLASS()
class URecepieUI : public UUserWidget
{
GENERATED_BODY()


public:

	UPROPERTY(BlueprintReadWrite);
	UCraftingRecepie* OwningRecepie = nullptr;

	UPROPERTY(BlueprintReadWrite)
	UBuildingUI* OwningUI = nullptr;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void InitialiceRecepieUI(UBuildingUI* ui, UCraftingRecepie* recepi);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UseRecepie();
};