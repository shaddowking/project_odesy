#pragma once
#include "SP_Resorce.h"
#include "SP_ItemStruct.generated.h"


USTRUCT(Blueprintable)
struct FItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USP_Resorse* ItemInfo = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ResorceAmount = 0;
};