#include "SP_ProjectileClass.h"
#include "Components/SphereComponent.h"
#include "SP_HealthComponent.h"


AProjectile::AProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("sphere");
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnProjectileHit);
	RootComponent = Sphere;
	PrimaryActorTick.bCanEverTick = true;
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActive)
	{
		AddActorLocalOffset(FVector::ForwardVector * Speed * DeltaTime, false);
		

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
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Ignore);

}

void AProjectile::DeActivate()
{
	SetActorHiddenInGame(true);
	IsActive = false;
	Sphere->SetCollisionProfileName(TEXT("NoCollision"));
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECR_Ignore);
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive)
	{
		AActor* HitActor = OtherActor;
		AProjectile* hitprojectile = Cast<AProjectile>(HitActor);
		if (HitActor && hitprojectile == nullptr)
		{

			UHealthComponent* healthComponent = HitActor->FindComponentByClass<UHealthComponent>();
			if (healthComponent)
			{
				healthComponent->TakeDamage(Damage);
			}

		}
		DeActivate();
	}
	
}


