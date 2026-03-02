#pragma once
#include "SP_Resorce.generated.h"

UCLASS()
class USP_Resorse : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Item")
	FString Name;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FSlateBrush BuffBrush;
};