#include "SP_SummenWratch.h"
#include "../../SP_Player.h"
#include "../SP_AbilityDataAsstet.h"
#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"
#include "../Projectiles/SP_Wratch.h"
#include "../SP_Subclass.h"

ASummonWratch::ASummonWratch()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASummonWratch::Tick(float DeltaTime)
{
	if (BIsAbilityActive && TargetingActor)
	{
		TargetLocation = Caster->GetPlacablePoint(5000);
		TargetingActor->SetActorLocation(TargetLocation);
	}
}

void ASummonWratch::OnAbilityPressed()
{
	BIsAbilityActive = true;
	OwnerSubclass->ActiveAbility = this;
	Caster->bIsUsingAbility = true;
	if (TargetingActor)
	{
		TargetingActor->GetRootComponent()->SetVisibility(true, true);

	}

	if (!TargetingActor && TargetingTemplate)
	{
		TargetingActor = GetWorld()->SpawnActor(TargetingTemplate);
	}
}

void ASummonWratch::OnAbilityReleas()
{
	
}

void ASummonWratch::ActivateCooldown()
{
	ActiveCooldown = 0;
	CooldownTimer();
}

void ASummonWratch::AbilitySelected()
{
	Caster->bIsPrimaryAbilityReady = false;
	BIsAbilityActive = false;
	Caster->bIsUsingAbility = false;
	OwnerSubclass->ActiveAbility = nullptr;
	IsInChosenSubclass = true;
	Hud->PlayerHudWidget->UpdatePrimaryAbilityIcon(AbilityBaseStates->AbilityInfo.AbilityIcon);
	ActivateCooldown();
}

void ASummonWratch::CooldownCompleted()
{
	Hud->PlayerHudWidget->UpdatePrimaryAbilityPercent(0);
	Caster->bIsPrimaryAbilityReady = true;
}

void ASummonWratch::UpdateUI(float Value)
{
	Super::UpdateUI(Value);
	Hud->PlayerHudWidget->UpdatePrimaryAbilityPercent(CooldownPercent);
}

void ASummonWratch::OnAbilityPrimaryAttack()
{
	Caster->bIsPrimaryAbilityReady = false;
	BIsAbilityActive = false;
	TargetingActor->GetRootComponent()->SetVisibility(false, true);


	if (!CreatedWratch)
	{
		CreatedWratch = GetWorld()->SpawnActor<AWratch>(WratchTemplate, TargetLocation, FRotator::ZeroRotator);
		CreatedWratch->InitialicePlaceblecharacter(Caster);
		CreatedWratch->DeActivate();
	}

	CreatedWratch->Activate(TargetLocation + GetActorUpVector() * 100);
	Caster->bIsUsingAbility = false;
	OwnerSubclass->ActiveAbility = nullptr;

	ActivateCooldown();
}

void ASummonWratch::OnAbilityPrimaryAttackRelease()
{
}

void ASummonWratch::OnAbilitySecendaryAttack()
{
}

void ASummonWratch::OnAbilitySecendaryAttackRealese()
{
}


