#include "SP_StormsEye.h"
#include "../../SP_Player.h"
#include "../SP_AbilityDataAsstet.h"
#include "../Projectiles/SP_StormTurret.h"

AStormsEye::AStormsEye()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AStormsEye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (BIsAbilityActive && TargetingActor)
	{
		TargetLocation = Caster->GetPlacablePoint(10000);
		TargetingActor->SetActorLocation(TargetLocation);
	}

	
}

void AStormsEye::OnAbilityPressed()
{
	BIsAbilityActive = true;
	if (TargetingActor)
	{
		TargetingActor->GetRootComponent()->SetVisibility(true, true);

	}
	
	if (!TargetingActor && TargetingTemplate)
	{
		TargetingActor = GetWorld()->SpawnActor(TargetingTemplate);
	}


}

void AStormsEye::OnAbilityReleas()
{
	BIsAbilityActive = false;
	FRotator Rotation = FRotator::ZeroRotator;
	TargetingActor->GetRootComponent()->SetVisibility(false, true);


	if (!CreatedTurret)
	{
		CreatedTurret = GetWorld()->SpawnActor<AStormTurret>(TurretRefrence, TargetLocation, Rotation);
	}
	
	
	CreatedTurret->Activate(TargetLocation);
	
}

void AStormsEye::ActivateCooldown(float Time)
{
	ActiveCooldown = 0;
	CooldownTimer();
}

void AStormsEye::CooldownTimer()
{
	if (ActiveCooldown < AbilityBaseStates->AbilityInfo.Cooldown)
	{
		ActiveCooldown++;
		FTimerHandle GunTimerHandle;

		GetWorldTimerManager().SetTimer(GunTimerHandle, this, &AStormsEye::CooldownTimer, 1, false);
	}
}
