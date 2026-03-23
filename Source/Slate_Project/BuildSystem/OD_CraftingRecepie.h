#pragma once
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/Class.h"

#include "OD_CraftingRecepie.generated.h"
class UCraftingRecepie;
class UCraftUI;
UCLASS()
class URecepieCraft : public UObject
{
GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCraftingRecepie* CraftingRecepie = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float CurrentDuration = 0;

	UPROPERTY(BlueprintReadWrite)
	UCraftUI* owningUI = nullptr;
};