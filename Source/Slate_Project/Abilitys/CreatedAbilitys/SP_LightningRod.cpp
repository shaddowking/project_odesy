#include "SP_LightningRod.h"
#include "../SP_AbilityDataAsstet.h"
#include "../Projectiles/SP_LightningRodStrike.h"
#include "../../SP_Player.h"

#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"
#include "../SP_Subclass.h"
#include "../../Buffes/SP_BuffDataAsset.h"
#include "../../Buffes/SP_Amplifide.h"

void ALightningRod::OnAbilityPressed()
{
	Caster->bIsElementalAbilityReady = false;
	OwnerSubclass->ActiveAbility = this;
	Caster->bIsUsingAbility = true;
	FVector SpawnLocation = Caster->GetActorLocation();

	if (LightningTemplate && !SpawndLightning)
	{
		SpawndLightning = GetWorld()->SpawnActor<ALightningRodStrike>(LightningTemplate,SpawnLocation , FRotator::ZeroRotator);
		
	}

	SpawndLightning->Activate(SpawnLocation);
	if (BuffToApply)
	{
		

		if (BuffToApply->CreatedBuff)
		{
			newBuff = BuffToApply->CreatedBuff;
		}
		else
		{
			newBuff = NewObject<UAmplifide>(BuffToApply);
			BuffToApply->CreatedBuff = newBuff;

		}
		Caster->AddBuff(newBuff,BuffToApply);

	}
	OwnerSubclass->ActiveAbility = nullptr;
	Caster->bIsUsingAbility = false;
	ActivateCooldown();
	newBuff = nullptr;


}

void ALightningRod::OnAbilityReleas()
{
}

void ALightningRod::ActivateCooldown()
{

	ActiveCooldown = 0;
	CooldownTimer();
}

void ALightningRod::AbilitySelected()
{
	Caster->bIsElementalAbilityReady = false;
	OwnerSubclass->ActiveAbility = nullptr;
	Caster->bIsUsingAbility = false;
	IsInChosenSubclass = true;
	Hud->PlayerHudWidget->UpdateElementAbilityIcon(AbilityBaseStates->AbilityInfo.AbilityIcon);
	ActivateCooldown();
}



void ALightningRod::CooldownCompleted()
{
	Hud->PlayerHudWidget->UpdateElementalAbilityPercent(0);
	Caster->bIsElementalAbilityReady = true;
}

void ALightningRod::UpdateUI(float Value)
{

	Super::UpdateUI(Value);
	Hud->PlayerHudWidget->UpdateElementalAbilityPercent(CooldownPercent);
}

void ALightningRod::OnAbilityPrimaryAttack()
{
}

void ALightningRod::OnAbilityPrimaryAttackRelease()
{
}

void ALightningRod::OnAbilitySecendaryAttack()
{
}

void ALightningRod::OnAbilitySecendaryAttackRealese()
{
}


