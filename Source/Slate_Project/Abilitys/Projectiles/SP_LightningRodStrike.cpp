#include "SP_LightningRodStrike.h"
#include "Components/SphereComponent.h"

#include "../../SP_HealthComponent.h"
#include "../../SP_Player.h"

ALightningRodStrike::ALightningRodStrike()
{

	AttackRadius = CreateDefaultSubobject<USphereComponent>("AttackRadius");
	AttackRadius->SetupAttachment(Root);
	AttackRadius->OnComponentBeginOverlap.AddDynamic(this, &ALightningRodStrike::OnEnemyenter);
	AttackRadius->OnComponentEndOverlap.AddDynamic(this, &ALightningRodStrike::OnEnemyexit);

}

void ALightningRodStrike::Activate(FVector Location)
{
	Super::Activate(Location);
	AttackRadius->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	BPActivate(Location);
	
	FTimerHandle AbilityTimerHandle;

	GetWorldTimerManager().SetTimer(AbilityTimerHandle, this, &ALightningRodStrike::LightningStrike, 0.5f, false);



}

void ALightningRodStrike::DeActivate()
{
	Super::DeActivate();
	AttackRadius->SetCollisionProfileName(TEXT("NoCollision"));

}

void ALightningRodStrike::LightningStrike()
{
	for (ACharacter* target : ListOfTargets) {

		UHealthComponent* healthComponent = target->FindComponentByClass<UHealthComponent>();
		if (healthComponent)
		{
			healthComponent->TakeDamage(Damage);
		}
	}
}

void ALightningRodStrike::OnEnemyenter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASPCharacter* player = Cast<ASPCharacter>(OtherActor);

	if (!player)
	{
		ACharacter* FoundTarget = Cast<ACharacter>(OtherActor);
		if (FoundTarget)
		{

			ListOfTargets.Add(FoundTarget);
		}
	}

	
}

void ALightningRodStrike::OnEnemyexit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* FoundTarget = Cast<ACharacter>(OtherActor);

	if (FoundTarget)
	{
		if (ListOfTargets.Contains(FoundTarget))
		{
			ListOfTargets.Remove(FoundTarget);
		}
	}
}
