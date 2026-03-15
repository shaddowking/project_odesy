#pragma once
#include "../SP_AbilityPlacableCharacter.h"
#include "SP_Wratch.generated.h"

class USphereComponent;
class AEnemyBase;
class AProjectile;
UCLASS()
class AWratch : public AAbilityPlacableCharacter
{
	GENERATED_BODY()

public:

	AWratch();

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float AttackInterval = 3;



	void Spawned() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* FirePoint = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* AttackRange = nullptr;

	void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTargetEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTargetExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Activate(FVector Location) override;

	void DeActivate() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	int ProjectilePoolsice = 50;

	UPROPERTY(BlueprintReadOnly)
	TArray<AProjectile*> WratchProjectilePool;

	UFUNCTION()
	AProjectile* GetNextAvalableWratchProjectile();

	AProjectile* AddWratchProjectileTooPool();

	void CreateWratchProjectilePool();

	UFUNCTION()
	void performAttack();

private:

	float CurrentAttackInterval = 0;

	AEnemyBase* CurrentTarget = nullptr;
	AEnemyBase* NewTarget = nullptr;

	AEnemyBase* GetClosestTarget();

	FVector ShootDirection;
	FVector RotateDirection;
	AProjectile* result = nullptr;
	AProjectile* createdprojectile = nullptr;
	AProjectile* CurentBullet = nullptr;
	

};