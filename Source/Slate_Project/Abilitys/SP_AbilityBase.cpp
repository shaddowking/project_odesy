#include "SP_AbilityBase.h"
#include "SP_AbilityDataAsstet.h"

void AAbilityBase::InitialiceAbility(ASPCharacter* player)
{
	Caster = player;
	Hud = Cast<ASP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

}

FVector AAbilityBase::GetUltimateSpawnLocation() {
	return FVector::ZeroVector;
}

void AAbilityBase::CooldownTimer()
{
	if (ActiveCooldown <= AbilityBaseStates->AbilityInfo.Cooldown)
	{
		ActiveCooldown += 0.1f;
		UpdateUI(ActiveCooldown);
		CooldownPercent = ActiveCooldown / AbilityBaseStates->AbilityInfo.Cooldown;
		FTimerHandle GunTimerHandle;

		GetWorldTimerManager().SetTimer(GunTimerHandle, this, &AAbilityBase::CooldownTimer, 0.1f, false);
	}
	else
	{
		CooldownCompleted();
	}
	
}

void AAbilityBase::CooldownCompleted()
{
	

}

void AAbilityBase::UpdateUI(float Value)
{
	
}
