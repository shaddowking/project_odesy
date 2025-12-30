#include "SP_AbilityProjectile.h"
#include "Components/SphereComponent.h"
#include "../SP_Player.h"
#include "../SP_HealthComponent.h"

AAbilityProjectile::AAbilityProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("sphere");
	RootComponent = Sphere;

	PrimaryActorTick.bCanEverTick = true;
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAbilityProjectile::OnProjectileHit);
}



void AAbilityProjectile::Tick(float DeltaTime)
{
	if (bIsActive)
	{
		FHitResult SweepHit;
		AddActorLocalOffset(FVector::ForwardVector * Speed * DeltaTime, false);
		
	}
	
}

void AAbilityProjectile::InitialiceProjectile(ASPCharacter* caster)
{
	owner = caster;
}

void AAbilityProjectile::OnProjectileHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && bIsActive == true)
	{
		UHealthComponent* healthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
		if (healthComponent)
		{
			healthComponent->TakeDamage(Stats.ImpactDamage);
		}
		bIsActive = false;

	}
}


