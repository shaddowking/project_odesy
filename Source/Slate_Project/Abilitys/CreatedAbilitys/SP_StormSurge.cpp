#include "SP_StormSurge.h"
#include "../../SP_Player.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Projectiles/SP_VoletileStormProjectile.h"

#include "../SP_AbilityDataAsstet.h"


void AStormSurge::OnAbilityPressed()
{
	FVector ShootDirection = Caster->GetAimPoint(5000) - GetUltimateSpawnLocation();
	projectile = GetWorld()->SpawnActor<ASPVoletileStormProjectile>(ProjectileRefrence, GetUltimateSpawnLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));
	projectile->bIsActive = true;
	ActivateCooldown(AbilityBaseStates->AbilityInfo.Cooldown);

}

void AStormSurge::OnAbilityReleas()
{
}

void AStormSurge::ActivateCooldown(float Time)
{

	ActiveCooldown = 0;
	CooldownTimer();
}

void AStormSurge::CooldownTimer()
{
	if (ActiveCooldown < AbilityBaseStates->AbilityInfo.Cooldown)
	{
		ActiveCooldown++;
		FTimerHandle GunTimerHandle;

		GetWorldTimerManager().SetTimer(GunTimerHandle, this, &AStormSurge::CooldownTimer, 1, false);
	}
}

FVector AStormSurge::GetUltimateSpawnLocation()
{
	
	FVector ViewOrigin;
	FRotator ViewRotation;



	Caster->GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

	FVector ViewForward = ViewRotation.Quaternion().GetForwardVector();
	FVector ViewUp = ViewRotation.Quaternion().GetUpVector();

	FVector Result = Caster->GetActorLocation() + ViewUp * 300 + ViewForward * 500;

	return FVector();
}
