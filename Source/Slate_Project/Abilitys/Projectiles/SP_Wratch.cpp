#include "SP_Wratch.h"
#include "Components/SphereComponent.h"
#include "../../Enemys/SP_EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../SP_ProjectileClass.h"

AWratch::AWratch()
{
	AttackRange = CreateDefaultSubobject<USphereComponent>("AttackRange");
	AttackRange->SetupAttachment(Root);
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AWratch::OnTargetEnter);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &AWratch::OnTargetExit);
	FirePoint = CreateDefaultSubobject<USceneComponent>("FirePoint");
	FirePoint->SetupAttachment(Root);

	PrimaryActorTick.bCanEverTick = true;
}

void AWratch::Spawned()
{
	Super::Spawned();
	CreateWratchProjectilePool();
}

void AWratch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsActive)
	{
		if (CurrentTarget)
		{

			ShootDirection = CurrentTarget->GetActorLocation() - GetActorLocation();
			RotateDirection = GetActorLocation() - CurrentTarget->GetActorLocation();

			SetActorRotation(UKismetMathLibrary::MakeRotFromX(RotateDirection));

			if (CurrentAttackInterval >= AttackInterval)
			{
				performAttack();
				CurrentAttackInterval = 0;
			}
			else
			{
				CurrentAttackInterval += DeltaTime;
			}
			
		}
	}
}

void AWratch::OnTargetEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	NewTarget = Cast<AEnemyBase>(OtherActor);

	if ( NewTarget != nullptr)
	{
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(OtherActor);
		FHitResult TargetHit;
		GetWorld()->LineTraceSingleByChannel(TargetHit, GetActorLocation(), OtherActor->GetActorLocation(), ECollisionChannel::ECC_Visibility, QueryParams);
		if (!TargetHit.bBlockingHit)
		{
			if (CurrentTarget)
			{
				CurrentTarget = GetClosestTarget();
			}
			else
			{
				CurrentTarget = Cast<AEnemyBase>(OtherActor);
			}
		}
	}
	
}

void AWratch::OnTargetExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == CurrentTarget)
	{
		CurrentTarget = nullptr;
	}
}

void AWratch::Activate(FVector Location)
{
	Super::Activate(Location);
	AttackRange->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWratch::DeActivate()
{
	Super::DeActivate();
	AttackRange->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

AProjectile* AWratch::GetNextAvalableWratchProjectile()
{
	AProjectile* result = nullptr;
	for (AProjectile* projectile : WratchProjectilePool)
	{
		if (projectile->IsActive == false)
		{
			result = projectile;
			break;
		}
	}

	if (result == nullptr)
	{
		result = AddWratchProjectileTooPool();
	}

	return result;
}

AProjectile* AWratch::AddWratchProjectileTooPool()
{


	AProjectile* createdprojectile = nullptr;

	createdprojectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, FVector::ZeroVector, GetActorRotation());
	WratchProjectilePool.Add(createdprojectile);
	createdprojectile->DeActivate();

	return createdprojectile;
}

void AWratch::CreateWratchProjectilePool()
{
	AProjectile* createdprojectile = nullptr;
	for (size_t i = 0; i < ProjectilePoolsice; i++)
	{

		createdprojectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), GetActorRotation());
		WratchProjectilePool.Add(createdprojectile);
		createdprojectile->DeActivate();

	}
}

void AWratch::performAttack()
{

	AProjectile* CurentBullet = GetNextAvalableWratchProjectile();

	CurentBullet->SetActorLocationAndRotation(FirePoint->GetComponentLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

	CurentBullet->Speed = 2000;
	CurentBullet->Damage = 20;
	CurentBullet->Activate();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Turret Attack"));
}

AEnemyBase* AWratch::GetClosestTarget()
{
	if (FVector::Distance(GetActorLocation(),NewTarget->GetActorLocation()) < FVector::Distance(GetActorLocation(), CurrentTarget->GetActorLocation()))
	{
		return NewTarget;
	}

	return CurrentTarget;
}


