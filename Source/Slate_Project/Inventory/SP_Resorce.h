#pragma once
#include "SP_Resorce.generated.h"

UCLASS()
class USP_Resorse : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FSlateBrush BuffBrush;
};