#include "SP_StormSurge.h"
#include "../../SP_Player.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Projectiles/SP_VoletileStormProjectile.h"
#include "../SP_AbilityDataAsstet.h"
#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"
#include "../SP_Subclass.h"



void AStormSurge::LanchProjectile()
{
	FVector ShootDirection = Caster->GetAimPoint(5000) - GetUltimateSpawnLocation();

	projectile->ProjectileActivate(GetUltimateSpawnLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

	OwnerSubclass->ActiveAbility = nullptr;
	Caster->bIsUsingAbility = false;

	ActivateCooldown();
}

void AStormSurge::OnAbilityPressed()
{
	Caster->bIsUltimateReady = false;
	OwnerSubclass->ActiveAbility = this;
	Caster->bIsUsingAbility = true;
	spawnDebug(Caster->GetAimPoint(5000));
	FVector ShootDirection = Caster->GetAimPoint(5000) - GetUltimateSpawnLocation();

	if (ProjectileRefrence && !projectile)
	{
		projectile = GetWorld()->SpawnActor<ASPVoletileStormProjectile>(ProjectileRefrence, GetUltimateSpawnLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));
		projectile->InitialiceProjectile(Caster);
	}

	

	projectile->ProjectileMove(GetUltimateSpawnLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));
	
	FTimerHandle AbilityTimerHandle;

	GetWorldTimerManager().SetTimer(AbilityTimerHandle, this, &AStormSurge::LanchProjectile, CastDelay, false);

	

}

void AStormSurge::OnAbilityReleas()
{

}
void AStormSurge::ActivateCooldown()
{

	ActiveCooldown = 0;
	Hud->PlayerHudWidget->UpdateUlitmateSliderColor(false);

	CooldownTimer();
}

void AStormSurge::AbilitySelected()
{
	Caster->bIsUltimateReady = false;
	OwnerSubclass->ActiveAbility = nullptr;
	Caster->bIsUsingAbility = false;
	IsInChosenSubclass = true;
	Hud->PlayerHudWidget->UpdateUltimateIcon(AbilityBaseStates->AbilityInfo.AbilityIcon);
	ActivateCooldown();

}



void AStormSurge::CooldownCompleted()
{
	Caster->bIsUltimateReady = true;
	Hud->PlayerHudWidget->UpdateUlitmateSliderColor(Caster->bIsUltimateReady);
	
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

void AStormSurge::OnAbilityPrimaryAttack()
{
}

void AStormSurge::OnAbilityPrimaryAttackRelease()
{
}

void AStormSurge::OnAbilitySecendaryAttack()
{
}

void AStormSurge::OnAbilitySecendaryAttackRealese()
{
}
