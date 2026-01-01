#pragma once
#include "GameFramework/Actor.h"
#include "SP_AbilityPlacable.generated.h"

UCLASS()
class AAbilityPlacable : public AActor {
	GENERATED_BODY()

public:
	
	AAbilityPlacable();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY()
	float duration = 10.0f;

	UPROPERTY(EditAnywhere)
	float Maxduration = 10.0f;

	void Activate(FVector Location);



	bool IsActive = false;
};