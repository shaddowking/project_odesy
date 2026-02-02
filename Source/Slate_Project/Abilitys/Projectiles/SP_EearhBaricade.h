#pragma once
#include "../SP_AbilityPlacable.h"
#include "SP_EearhBaricade.generated.h"

class UHealthComponent;
class UBoxComponent;

UCLASS()
class AEarthBaricade : public AAbilityPlacable
{
	GENERATED_BODY()

public:
	AEarthBaricade();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UHealthComponent* hpcomp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* baricadeCollision = nullptr;

	UFUNCTION()
	void OnBaricadeDamage();

	UFUNCTION()
	void OnBaricadeDeath();

	void Activate(FVector Location) override;

	void DeActivate() override;


};