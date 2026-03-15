#include "SP_VoletileStormProjectile.h"
#include "Components/SphereComponent.h"
#include "../../SP_Player.h"
#include "../../SP_HealthComponent.h"


ASPVoletileStormProjectile::ASPVoletileStormProjectile()
{
	
	ShockRange = CreateDefaultSubobject<USphereComponent>("ShockRange");
	ShockRange->SetupAttachment(RootComponent);
	ShockRange->OnComponentBeginOverlap.AddDynamic(this, &ASPVoletileStormProjectile::OnEnemyEnter);

	
}

void ASPVoletileStormProjectile::OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* FoundTarget = Cast<ACharacter>(OtherActor);
	if (FoundTarget && playerowner != FoundTarget)
	{
		StartLightningVFX(FoundTarget->GetActorLocation());
		healthComponent = FoundTarget->FindComponentByClass<UHealthComponent>();
		if (healthComponent)
		{
			healthComponent->TakeDamage(ShockDamage);
		}
		FoundTarget = nullptr;
		healthComponent = nullptr;
	}

	
}

void ASPVoletileStormProjectile::ProjectileActivate(FVector location, FRotator Rotation)
{
	Super::ProjectileActivate(location, Rotation);
	ShockRange->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


}

void ASPVoletileStormProjectile::ProjectileDeActivate()
{
	Super::ProjectileDeActivate();
	ShockRange->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}
