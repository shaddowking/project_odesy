#include "SP_ProjectileClass.h"
#include "Components/SphereComponent.h"
#include "SP_HealthComponent.h"


AProjectile::AProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("sphere");
	RootComponent = Sphere;
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FHitResult SweepHit;
	AddActorLocalOffset(FVector::ForwardVector * Speed * DeltaTime, true, &SweepHit);
	if (SweepHit.bBlockingHit)
	{
		AActor* HitActor = SweepHit.GetActor();
		if (HitActor)
		{
			
			UHealthComponent* healthComponent = HitActor->FindComponentByClass<UHealthComponent>();
			if (healthComponent)
			{
				healthComponent->TakeDamage(20);
			}
			
		}
		Destroy();
	}
}
