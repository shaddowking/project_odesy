#include "SP_StormTurret.h"
#include "Components/SphereComponent.h"
#include "../../SP_HealthComponent.h"
#include "../../SP_Player.h"



AStormTurret::AStormTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	TurretRange = CreateDefaultSubobject<USphereComponent>("Range");
	TurretRange->SetupAttachment(Root);
	TurretRange->OnComponentBeginOverlap.AddDynamic(this, &AStormTurret::OnEnemyEnter);
}

void AStormTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActive)
	{
		

		if (AttackTimer >= AttackInterval)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Turret Attack"));

			PerformAttack();
			AttackTimer = 0;
		}
		else
		{
			AttackTimer += DeltaTime;
		}

		if (duration <= 0)
		{
			Deactivate();
		}
		else
		{
			duration -= DeltaTime;
		}
	}


	
}

void AStormTurret::OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* FoundTarget = Cast<ACharacter>(OtherActor);
	if (FoundTarget)
	{
		ListOfTargets.Add(FoundTarget);
	}
}

void AStormTurret::OnEnemyExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void AStormTurret::Deactivate()
{
	SetActorHiddenInGame(true);
	IsActive = false;
}

void AStormTurret::PerformAttack()
{
	for (ACharacter* CurrentCharacter : ListOfTargets) {
		UHealthComponent* healthComponent = CurrentCharacter->FindComponentByClass<UHealthComponent>();
		if (healthComponent)
		{
			healthComponent->TakeDamage(10);
		}
		
	}
}
