#pragma once
#include "GameFramework/Actor.h"
#include "SP_AbilityProjectile.generated.h"

class USphereComponent;
class ASPCharacter;

USTRUCT(BlueprintType)
struct FAbilityprojectileStats 
{
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



	ASPCharacter* owner = nullptr;

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere = nullptr;

};