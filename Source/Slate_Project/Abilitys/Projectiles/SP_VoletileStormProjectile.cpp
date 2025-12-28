#include "SP_VoletileStormProjectile.h"
#include "Components/SphereComponent.h"


ASPVoletileStormProjectile::ASPVoletileStormProjectile()
{
	
	ShockRange = CreateDefaultSubobject<USphereComponent>("ShockRange");
	ShockRange->SetupAttachment(RootComponent);
	ShockRange->OnComponentBeginOverlap.AddDynamic(this, &ASPVoletileStormProjectile::OnEnemyEnter);

	
}

void ASPVoletileStormProjectile::OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* FoundTarget = Cast<ACharacter>(OtherActor);
	if (FoundTarget)
	{
		//Do ShockLogicHere
	}
}
