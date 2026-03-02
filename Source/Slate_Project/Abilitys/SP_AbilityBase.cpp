#include "SP_AbilityBase.h"
#include "SP_AbilityDataAsstet.h"

void AAbilityBase::InitialiceAbility(ASPCharacter* player, ASubclass* OwningSubclass)
{
	Caster = player;
	OwnerSubclass = OwningSubclass;
	Hud = Cast<ASP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

}

void AAbilityBase::AbilitySelected()
{
}



FVector AAbilityBase::GetUltimateSpawnLocation() {
	return FVector::ZeroVector;
}

void AAbilityBase::CooldownTimer()
{
	if (IsInChosenSubclass)
	{
		if (ActiveCooldown <= AbilityBaseStates->AbilityInfo.Cooldown)
		{
			ActiveCooldown += 0.1f;
			UpdateUI(ActiveCooldown);
			CooldownPercent = ActiveCooldown / AbilityBaseStates->AbilityInfo.Cooldown;
			FTimerHandle AbilityTimerHandle;

			GetWorldTimerManager().SetTimer(AbilityTimerHandle, this, &AAbilityBase::CooldownTimer, 0.1f, false);
		}
		else
		{
			CooldownCompleted();
		}
	}
	
	
}

void AAbilityBase::CooldownCompleted()
{
	

}

void AAbilityBase::UpdateUI(float Value)
{
	
}
