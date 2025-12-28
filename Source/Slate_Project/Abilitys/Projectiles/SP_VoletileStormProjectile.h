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
	
	USphereComponent* ShockRange = nullptr;


	UFUNCTION()
	void OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:

	
};