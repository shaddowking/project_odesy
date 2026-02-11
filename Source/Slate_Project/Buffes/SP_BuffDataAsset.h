#pragma once

#include "SP_BuffDataAsset.generated.h"

class UBuffBase;
class UGameplayEffect;
class UBuffUI;
UCLASS()
class UBuffDataAsset : public UDataAsset
{
GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UObject> BuffTemplate = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush BuffBrush;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBuffUI> buffUITemplate;

	UPROPERTY(EditAnywhere)
	FString Name;
	

	UPROPERTY(EditAnywhere)
	float Duration = 0;

	UPROPERTY(EditAnywhere)
	bool HasDuration = true;

};