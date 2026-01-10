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

	if (IsActive)
	{
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
			DeActivate();
		}

		if (Duration <= 0)
		{
			DeActivate();
		}
		else
		{
			Duration -= DeltaTime;
		}
	}
	
}

void AProjectile::Activate()
{
	Duration = MaxDuration;
	SetActorHiddenInGame(false);
	IsActive = true;
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AProjectile::DeActivate()
{
	SetActorHiddenInGame(true);
	IsActive = false;
	Sphere->SetCollisionProfileName(TEXT("NoCollision"));
}


