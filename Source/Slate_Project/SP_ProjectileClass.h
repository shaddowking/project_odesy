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

	UPROPERTY(EditAnywhere)
	float Speed = 2000.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	int Damage = 10;

	float Duration;

	UPROPERTY(EditDefaultsOnly, Category = "Duration")
	float MaxDuration = 10;

	UPROPERTY(BlueprintReadOnly)
	bool IsActive = false;

	void Activate();

	void DeActivate();

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere = nullptr;

};