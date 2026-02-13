#include "SP_GaiasVenginse.h"
#include "../SP_AbilityDataAsstet.h"
#include "../Projectiles/SP_LightningRodStrike.h"
#include "../../SP_Player.h"

#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"
#include "../SP_Subclass.h"
#include "../../Buffes/SP_BuffDataAsset.h"
#include "../../Buffes/SP_Amplifide.h"

void AGiasVeginse::OnAbilityPressed()
{
}

void AGiasVeginse::OnAbilityReleas()
{
}

void AGiasVeginse::ActivateCooldown()
{
}

void AGiasVeginse::AbilitySelected()
{
	Hud->PlayerHudWidget->UpdateUltimateIcon(AbilityBaseStates->AbilityInfo.AbilityIcon);

}

void AGiasVeginse::CooldownCompleted()
{
	Hud->PlayerHudWidget->UpdateUltimatePercent(0);
	Caster->bIsUltimateReady = true;
}

void AGiasVeginse::UpdateUI(float Value)
{
	Super::UpdateUI(Value);
	Hud->PlayerHudWidget->UpdateUltimatePercent(CooldownPercent);

}

void AGiasVeginse::OnAbilityPrimaryAttack()
{
}

void AGiasVeginse::OnAbilityPrimaryAttackRelease()
{
}

void AGiasVeginse::OnAbilitySecendaryAttack()
{
}

void AGiasVeginse::OnAbilitySecendaryAttackRealese()
{
}
