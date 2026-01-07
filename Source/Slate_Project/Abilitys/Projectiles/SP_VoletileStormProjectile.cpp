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
	ASPCharacter* target = Cast<ASPCharacter>(OtherActor);
	if (!target)
	{

		ACharacter* FoundTarget = Cast<ACharacter>(OtherActor);
		if (FoundTarget)
		{
			UHealthComponent* healthComponent = FoundTarget->FindComponentByClass<UHealthComponent>();
			if (healthComponent)
			{
				healthComponent->TakeDamage(ShockDamage);
			}
		}
	}

	
}
