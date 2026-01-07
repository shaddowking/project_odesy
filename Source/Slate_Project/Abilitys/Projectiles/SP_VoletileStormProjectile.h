#pragma once

#include "../SP_AbilityProjectile.h"
#include "SP_VoletileStormProjectile.generated.h"

class USphereComponent;


UCLASS()

class ASPVoletileStormProjectile : public AAbilityProjectile 
{
	GENERATED_BODY()

public:

	ASPVoletileStormProjectile();
	
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* ShockRange = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	int ShockDamage = 10;


	UFUNCTION()
	void OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:

	
};