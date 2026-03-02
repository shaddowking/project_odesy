#include "SP_CreateBaricade.h"
#include "../../SP_Player.h"
#include "../SP_AbilityDataAsstet.h"
#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"
#include "../Projectiles/SP_EearhBaricade.h"
#include "Kismet/KismetMathLibrary.h"
#include "../SP_Subclass.h"
AEarthBaricadeAbility::AEarthBaricadeAbility()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AEarthBaricadeAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BIsAbilityActive && BaricadeTargeting)
	{
		playerDirection = BaricadeTargeting->GetActorLocation() - Caster->Aimpoint->GetComponentLocation();
		TargetLocation = Caster->GetPlacablePoint(10000);
		CurrentTargetRotation = BaricadeTargeting->GetActorRotation();
		TargetingDirection = UKismetMathLibrary::MakeRotFromX(playerDirection);
		CurrentTargetRotation.Yaw = TargetingDirection.Yaw;
		BaricadeTargeting->SetActorRotation(CurrentTargetRotation);
		
		
		BaricadeTargeting->SetActorLocation(TargetLocation);
	}
}

void AEarthBaricadeAbility::LaunchAbility()
{
	createdBaricade->Activate(TargetLocation);
	createdBaricade->SetActorRotation(CurrentTargetRotation);
	Caster->bIsUsingAbility = false;
	OwnerSubclass->ActiveAbility = nullptr;
	ActivateCooldown();
}


void AEarthBaricadeAbility::OnAbilityPressed()
{
	BIsAbilityActive = true;
	OwnerSubclass->ActiveAbility = this;
	if (BaricadeTargeting)
	{
		BaricadeTargeting->GetRootComponent()->SetVisibility(true, true);

	}

	if (!BaricadeTargeting && BaricadeTargetingTemplate)
	{
		BaricadeTargeting = GetWorld()->SpawnActor(BaricadeTargetingTemplate);
	}
}

void AEarthBaricadeAbility::OnAbilityReleas()
{
	Caster->bIsElementalAbilityReady = false;
	BIsAbilityActive = false;
	FRotator Rotation = FRotator::ZeroRotator;
	BaricadeTargeting->GetRootComponent()->SetVisibility(false, true);

	if (!createdBaricade)
	{
		createdBaricade = GetWorld()->SpawnActor<AEarthBaricade>(placableTemplate, TargetLocation, Rotation);
		createdBaricade->InitialicePlaceble(Caster);
		createdBaricade->DeActivate();
	}

	FTimerHandle AbilityTimerHandle;

	GetWorldTimerManager().SetTimer(AbilityTimerHandle, this, &AEarthBaricadeAbility::LaunchAbility, CastDelay, false);
}

void AEarthBaricadeAbility::ActivateCooldown()
{
	ActiveCooldown = 0;
	CooldownTimer();
}

void AEarthBaricadeAbility::AbilitySelected()
{
	Caster->bIsElementalAbilityReady = false;
	BIsAbilityActive = false;
	OwnerSubclass->ActiveAbility = nullptr;
	IsInChosenSubclass = true;
	Hud->PlayerHudWidget->UpdateElementAbilityIcon(AbilityBaseStates->AbilityInfo.AbilityIcon);
	ActivateCooldown();
}

void AEarthBaricadeAbility::CooldownCompleted()
{
	Hud->PlayerHudWidget->UpdateElementalAbilityPercent(0);
	Caster->bIsElementalAbilityReady = true;
}

void AEarthBaricadeAbility::UpdateUI(float Value)
{
	Super::UpdateUI(Value);
	Hud->PlayerHudWidget->UpdateElementalAbilityPercent(CooldownPercent);
}

void AEarthBaricadeAbility::OnAbilityPrimaryAttack()
{
}

void AEarthBaricadeAbility::OnAbilityPrimaryAttackRelease()
{
}

void AEarthBaricadeAbility::OnAbilitySecendaryAttack()
{
}

void AEarthBaricadeAbility::OnAbilitySecendaryAttackRealese()
{
}


