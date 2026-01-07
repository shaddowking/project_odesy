#include "SP_LightningRod.h"
#include "../SP_AbilityDataAsstet.h"
#include "../Projectiles/SP_LightningRodStrike.h"
#include "../../SP_Player.h"

#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"


void ALightningRod::OnAbilityPressed()
{
	Caster->bIsElementalAbilityReady = false;
	FVector SpawnLocation = Caster->GetActorLocation();

	if (LightningTemplate && !SpawndLightning)
	{
		SpawndLightning = GetWorld()->SpawnActor<ALightningRodStrike>(LightningTemplate,SpawnLocation , FRotator::ZeroRotator);
		
	}

	SpawndLightning->Activate(SpawnLocation);
	ActivateCooldown();



}

void ALightningRod::OnAbilityReleas()
{
}

void ALightningRod::ActivateCooldown()
{

	ActiveCooldown = 0;
	CooldownTimer();
}

void ALightningRod::InitialiceAbility(ASPCharacter* player)
{
	Super::InitialiceAbility(player);
	Hud->PlayerHudWidget->UpdateElementAbilityIcon(AbilityBaseStates->AbilityInfo.AbilityIcon);
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


