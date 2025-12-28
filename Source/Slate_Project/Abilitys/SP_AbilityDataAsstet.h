#pragma once
#include "SP_AbilityDataAsstet.generated.h"

USTRUCT(Blueprintable)
struct FAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString AbilityName;

	UPROPERTY(EditAnywhere)
	UTexture2D* AbilityIcon;

	UPROPERTY(EditAnywhere)
	float Cooldown = 0;
};



UCLASS()
class UAbilityDataAsset : public UDataAsset {
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FAbilityInfo AbilityInfo;
};
