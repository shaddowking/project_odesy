#include "SP_StormsEye.h"
#include "../../SP_Player.h"
#include "../SP_AbilityDataAsstet.h"
#include "../Projectiles/SP_StormTurret.h"
#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"


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
	Caster->bIsPrimaryAbilityReady = false;
	BIsAbilityActive = false;
	FRotator Rotation = FRotator::ZeroRotator;
	TargetingActor->GetRootComponent()->SetVisibility(false, true);


	if (!CreatedTurret)
	{
		CreatedTurret = GetWorld()->SpawnActor<AStormTurret>(TurretRefrence, TargetLocation, Rotation);
		CreatedTurret->InitialicePlaceble(Caster);
	}
	
	
	CreatedTurret->Activate(TargetLocation);
	ActivateCooldown();
	
}

void AStormsEye::ActivateCooldown()
{
	ActiveCooldown = 0;
	CooldownTimer();
}

void AStormsEye::CooldownCompleted()
{
	Hud->PlayerHudWidget->UpdatePrimaryAbilityPercent(0);
	Caster->bIsPrimaryAbilityReady = true;
}

void AStormsEye::UpdateUI(float Value)
{
	Super::UpdateUI(Value);
	Hud->PlayerHudWidget->UpdatePrimaryAbilityPercent(CooldownPercent);
}

void AStormsEye::InitialiceAbility(ASPCharacter* player)
{
	Super::InitialiceAbility(player);
	Hud->PlayerHudWidget->UpdatePrimaryAbilityIcon(AbilityBaseStates->AbilityInfo.AbilityIcon);
}

