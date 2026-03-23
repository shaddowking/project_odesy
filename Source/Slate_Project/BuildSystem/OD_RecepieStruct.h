#pragma once
#include "../Inventory/SP_ItemStruct.h"
#include "OD_RecepieStruct.generated.h"

USTRUCT(Blueprintable)
struct FRecepieStruct
{

	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FItem Input;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItem Output;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration = 10;

};

class UCraftUI;

UCLASS()
class UCraftingRecepie : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString RecepieName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRecepieStruct recepie;

	

};