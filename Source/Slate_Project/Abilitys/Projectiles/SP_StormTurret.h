#pragma once
#include "../SP_AbilityPlacable.h"
#include "SP_StormTurret.generated.h"

class USphereComponent;
class UHealthComponent;

UCLASS()
class AStormTurret : public AAbilityPlacable 
{
	GENERATED_BODY()

public:

	AStormTurret();

	void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* TurretRange = nullptr;

	UFUNCTION()
	void OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEnemyExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<ACharacter*> ListOfTargets;

	UPROPERTY(EditDefaultsOnly)
	float AttackInterval = 2.0f;

	virtual void DeActivate() override;

	virtual void Activate(FVector Location) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdeteCoreShader(float percent);


private:

	void PerformAttack();

	float AttackTimer = 0.0f;

	UHealthComponent* healthComponent = nullptr;

};