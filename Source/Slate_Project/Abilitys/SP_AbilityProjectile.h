#pragma once
#include "GameFramework/Actor.h"
#include "SP_AbilityProjectile.generated.h"

class USphereComponent;
class ASPCharacter;

USTRUCT(BlueprintType)
struct FAbilityprojectileStats 
{
	GENERATED_BODY()

	float ImpactDamage = 50;
	
};

UCLASS(Abstract)
class AAbilityProjectile : public AActor {
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsActive = false;

	AAbilityProjectile();

	void Tick(float DeltaTime) override;

	virtual void InitialiceProjectile(ASPCharacter* caster);

	UPROPERTY(EditAnywhere)
	FAbilityprojectileStats Stats;

	UPROPERTY(EditAnywhere)
	float Speed = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	int ImpactDamage = 50;

	float Duration;

	UPROPERTY(EditDefaultsOnly, Category = "BaseValue")
	float MaxDuration = 10;

	ASPCharacter* owner = nullptr;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	virtual void ProjectileActivate(FVector location,FRotator Rotation);

	UFUNCTION(BlueprintImplementableEvent)
	void BPActivate(FVector location);

	UFUNCTION(BlueprintImplementableEvent)
	void BPMove(FVector location);

	virtual void ProjectileMove(FVector location, FRotator Rotation);

	virtual void ProjectileDeActivate();


private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere = nullptr;



};