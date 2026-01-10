#pragma once 
#include "../SP_AbilityPlacable.h"
#include "SP_LightningRodStrike.generated.h"

class USphereComponent;

UCLASS()
class ALightningRodStrike : public AAbilityPlacable 
{
	GENERATED_BODY()

public:

	ALightningRodStrike();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* AttackRadius = nullptr;

	virtual void Activate(FVector Location) override;

	virtual void DeActivate() override;


	void LightningStrike();

	UFUNCTION()
	void OnEnemyenter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEnemyexit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<ACharacter*> ListOfTargets;

};