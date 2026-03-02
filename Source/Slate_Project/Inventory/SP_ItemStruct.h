#pragma once
#include "SP_Resorce.h"
#include "SP_ItemStruct.generated.h"


USTRUCT(Blueprintable)
struct FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USP_Resorse* ItemInfo = nullptr;

	UPROPERTY(EditAnywhere)
	int ResorceAmount = 0;
};