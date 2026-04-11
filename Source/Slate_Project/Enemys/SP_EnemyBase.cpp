#include "SP_EnemyBase.h"
#include "../SP_HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../AI/OD_AIEnemyController.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


#include "Kismet/KismetMathLibrary.h"


AEnemyBase::AEnemyBase()
{
	HPComp = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HPComp->OnDamage.AddDynamic(this, &AEnemyBase::OnDamage);
	HPComp->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
	World = GetWorld();
	
}

void AEnemyBase::FieldOfViewCheck()
{

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), Radius, objectTypes, ACharacter::StaticClass(), ActorsToIgnore,targetList);
	bestdistance = Radius * 10;

	for(AActor* target : targetList)
	{
		FTransform targetTransform = target->GetActorTransform();
		FVector directionToTarget = (targetTransform.GetLocation() - GetActorLocation()).GetSafeNormal();


		if (FVector::DotProduct(GetActorLocation(), directionToTarget) < angle)
		{
			float distanceToTarget = FVector::Distance(GetActorLocation(), targetTransform.GetLocation());
			FHitResult FovHit;
			GetWorld()->LineTraceSingleByChannel(FovHit, GetActorLocation(), targetTransform.GetLocation(), ECollisionChannel::ECC_Visibility);

			if (!FovHit.bBlockingHit)
			{
				if (distanceToTarget < bestdistance)
				{
					bestdistance = distanceToTarget;
					TargetActor = target;
				}
			}
		}
	}
	if (TargetActor)
	{
		BlackboardComp->SetValueAsObject("Target", TargetActor);
	}

	
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FieldOfViewCheck();
	if (TargetActor && !bIsDead)
	{
		MyLocation = GetActorLocation();
		TargetLocation = TargetActor->GetActorLocation();
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation);
		NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, InterpSpeed);
		SetActorRotation(NewRotation);



	}
}

void AEnemyBase::OnDamage()
{
	BPOnDamage();
}

void AEnemyBase::OnDeath()
{
	bIsDead = true;
	Cast<AAIController>(GetController())->GetBrainComponent()->StopLogic(TEXT("Stopped by user action"));
	GetCharacterMovement()->StopMovementImmediately();
	SetActorHiddenInGame(true);
	BPOnDeath();
}

void AEnemyBase::BeginPlay()
{
	ActorsToIgnore.Add(this);
	Super::BeginPlay();
	BlackboardComp = Cast<AEnemyController>(GetController())->GetBlackboardComponent();
		
}
