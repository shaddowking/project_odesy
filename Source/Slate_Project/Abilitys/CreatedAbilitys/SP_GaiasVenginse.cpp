#include "SP_GaiasVenginse.h"
#include "../SP_AbilityDataAsstet.h"
#include "../Projectiles/SP_LightningRodStrike.h"
#include "../../SP_Player.h"

#include "../../UI/SP_HUD.h"
#include "../../UI/SP_PlayerHud.h"
#include "../SP_Subclass.h"
#include "../Projectiles/SP_GiasTotem.h"
#include "../../Buffes/SP_BuffDataAsset.h"
#include "../../Buffes/SP_Amplifide.h"

AGiasVeginse::AGiasVeginse()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGiasVeginse::OnAbilityPressed()
{
	Caster->bIsUltimateReady = false;
	OwnerSubclass->ActiveAbility = this;
	Caster->bIsUsingAbility = true;


	if (Caster->bIsGrounded)
	{
		// Perform Ultimate
		CreateTotem();
	}
	else if (Caster->bIsGrounded == false)
	{
		MovePlayerToGround();
	}
}

void AGiasVeginse::OnAbilityReleas()
{
}

void AGiasVeginse::ActivateCooldown()
{
	ActiveCooldown = 0;
	Hud->PlayerHudWidget->UpdateUlitmateSliderColor(false);

	CooldownTimer();
}

void AGiasVeginse::AbilitySelected()
{
	Caster->bIsUltimateReady = false;
	OwnerSubclass->ActiveAbility = nullptr;
	Caster->bIsUsingAbility = false;
	IsInChosenSubclass = true;
	Hud->PlayerHudWidget->UpdateUltimateIcon(AbilityBaseStates->AbilityInfo.AbilityIcon);
	ActivateCooldown();

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

void AGiasVeginse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltatime = DeltaTime;
}

FVector AGiasVeginse::GetUltimateSpawnLocation()
{
	FVector Result;
	FHitResult AimHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(AimHit,Caster->GetActorLocation() + (Caster->GetActorForwardVector() * 500 + Caster->GetActorUpVector() * 10), Caster->GetActorLocation() + (Caster->GetActorForwardVector() * 100 + Caster->GetActorUpVector() *- 3000), ECollisionChannel::ECC_Visibility, QueryParams);

	Result = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	return Result;
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

void AGiasVeginse::CreateTotem()
{
	
	FVector SpawnLocation = GetUltimateSpawnLocation();
	
	spawnDebug(SpawnLocation);


	if (!CreatedTotem && totamTemplate)
	{
		FRotator Rotation = FRotator::ZeroRotator;

		CreatedTotem = GetWorld()->SpawnActor<AGiasTotem>(totamTemplate, SpawnLocation, Rotation);
		CreatedTotem->InitialicePlaceble(Caster);
		CreatedTotem->DeActivate();
	}

	if (CreatedTotem)
	{
		CreatedTotem->Activate(SpawnLocation);
	}
	
	//PrimaryActorTick.bCanEverTick = false;
	OwnerSubclass->ActiveAbility = nullptr;
	Caster->bIsUsingAbility = false;

	ActivateCooldown();

}

void AGiasVeginse::MovePlayerToGround()
{


	Caster->AddActorLocalOffset(FVector::DownVector * MoveDownSpeed * (deltatime), false);

	if (Caster->bIsGrounded == false)
	{
		FTimerHandle AbilityTimerHandle;

		GetWorldTimerManager().SetTimer(AbilityTimerHandle, this, &AGiasVeginse::MovePlayerToGround, 0.01, false);
	}
	else
	{
		CreateTotem();

	}

}
