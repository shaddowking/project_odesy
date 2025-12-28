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

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere = nullptr;

};