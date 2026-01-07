#include "SP_StormSurge.h"
#include "../../SP_Player.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Projectiles/SP_VoletileStormProjectile.h"

#include "../SP_AbilityDataAsstet.h"
#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"



void AStormSurge::OnAbilityPressed()
{
	Caster->bIsUltimateReady = false;
	FVector ShootDirection = Caster->GetAimPoint(5000) - GetUltimateSpawnLocation();
	spawnDebug(Caster->GetAimPoint(5000));

	if (ProjectileRefrence && !projectile)
	{
		projectile = GetWorld()->SpawnActor<ASPVoletileStormProjectile>(ProjectileRefrence, GetUltimateSpawnLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));
		projectile->InitialiceProjectile(Caster);
	}

	projectile->ProjectileActivate(GetUltimateSpawnLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));
	
	ActivateCooldown();

}

void AStormSurge::OnAbilityReleas()
{
}

void AStormSurge::ActivateCooldown()
{

	ActiveCooldown = 0;
	CooldownTimer();
}

void AStormSurge::CooldownCompleted()
{
	Hud->PlayerHudWidget->UpdateUltimatePercent(0);
	Caster->bIsUltimateReady = true;
}

void AStormSurge::UpdateUI(float Value)
{
	Super::UpdateUI(Value);

	Hud->PlayerHudWidget->UpdateUltimatePercent(CooldownPercent);
}





FVector AStormSurge::GetUltimateSpawnLocation()
{
	
	FVector ViewOrigin;
	FRotator ViewRotation;



	Caster->GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

	FVector ViewForward = ViewRotation.Quaternion().GetForwardVector();
	FVector ViewUp = ViewRotation.Quaternion().GetUpVector();
	

	FVector Result = Caster->GetActorLocation() + ViewUp * 100 + Caster->GetActorForwardVector() * 200;

	return Result;
}
