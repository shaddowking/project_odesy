#pragma once
#include "GameFramework/Actor.h"
#include "SP_ProjectileClass.generated.h"

class USphereComponent;
class ASPCharacter;

UCLASS()
class AProjectile : public AActor {
	GENERATED_BODY()

public:
	AProjectile();

	void Tick(float DeltaTime) override;

	UPROPERTY()
	ASPCharacter* Owningplayer = nullptr;

	UPROPERTY(EditAnywhere)
	float Speed = 2000.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	int Damage = 10;

	float Duration;

	UPROPERTY(EditDefaultsOnly, Category = "Duration")
	float MaxDuration = 5;

	UPROPERTY(BlueprintReadOnly)
	bool IsActive = false;

	UFUNCTION()
	void Activate();

	UFUNCTION()
	void DeActivate();

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere = nullptr;

};