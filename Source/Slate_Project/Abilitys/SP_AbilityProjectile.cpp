#include "SP_AbilityProjectile.h"
#include "Components/SphereComponent.h"
#include "../SP_Player.h"
#include "../SP_HealthComponent.h"

AAbilityProjectile::AAbilityProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("sphere");
	RootComponent = Sphere;
	PrimaryActorTick.bCanEverTick = true;
}



void AAbilityProjectile::Tick(float DeltaTime)
{
	if (bIsActive)
	{
		FHitResult SweepHit;
		AddActorLocalOffset(FVector::ForwardVector * Speed * DeltaTime, true, &SweepHit);
		AActor* HitActor = SweepHit.GetActor();
		if (HitActor)
		{

			UHealthComponent* healthComponent = HitActor->FindComponentByClass<UHealthComponent>();
			if (healthComponent)
			{
				healthComponent->TakeDamage(Stats.ImpactDamage);
			}

		}
		Destroy();
	}
	
}

void AAbilityProjectile::InitialiceProjectile(ASPCharacter* caster)
{
	owner = caster;
}


