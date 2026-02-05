#include "SP_Gun.h"
#include "Kismet/KismetMathLibrary.h"
#include "SP_GunConponent.h"
#include "SP_Player.h"
#include "SP_ProjectileClass.h"
#include "UI/SP_PlayerHud.h"
#include "UI/SP_HUD.h"

ASP_Gun::ASP_Gun()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("RootComonent");
	RootComponent = Root;

	FirePoint = CreateDefaultSubobject<USceneComponent>("FirePoint");
	FirePoint->SetupAttachment(Root);

	GunComponent = CreateDefaultSubobject<USP_GunComponent>("GunComponent");
	GunComponent->OnShoot.AddDynamic(this, &ASP_Gun::GunFire);
	GunComponent->OnRealese.AddDynamic(this, &ASP_Gun::GunRealese);
	GunComponent->OnActivate.AddDynamic(this, &ASP_Gun::Activate);
	GunComponent->OnDeactivate.AddDynamic(this, &ASP_Gun::DeActivate);
	GunComponent->OwningGun = this;

}

void ASP_Gun::BeginPlay()
{
	Super::BeginPlay();
	GunComponent->CurrentAmmo = GunComponent->MaxAmmo;
	hud = Cast<ASP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

}

void ASP_Gun::GunFire()
{
	
	switch (GunComponent->Guntype)
	{
	case EGunType::FullAuto:
		FullAuto();
		break;
	case EGunType::SemiAuto:
		SemiAuto();
		break;
	case EGunType::Burst:
		burstsMade = 0;
		Burst();
		break;
	case EGunType::Charge:
		Charge();
		break;
	default:
		break;
	}
}

void ASP_Gun::GunRealese()
{

	

	switch (GunComponent->Guntype)
	{
	case EGunType::FullAuto:
		
		break;
	case EGunType::SemiAuto:
		GunComponent->Owner->ResetTimeBetwenShots();
		break;
	case EGunType::Burst:
		
		break;
	case EGunType::Charge:
		ChargeRelease();
		break;
	default:
		break;
	}
}

void ASP_Gun::Activate()
{
	SetActorHiddenInGame(false);
}

void ASP_Gun::DeActivate()
{
	SetActorHiddenInGame(true);
}

void ASP_Gun::SpawnBullet(FVector AimPoint, USceneComponent* GunFirePoint, float DamageModefire)
{

	FVector ShootDirection = AimPoint - GunFirePoint->GetComponentLocation();



	AProjectile* CurentBullet = GunComponent->Owner->GetNextAvalableProjectile();

	CurentBullet->SetActorLocationAndRotation(GunFirePoint->GetComponentLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

	CurentBullet->Speed = GunComponent->BulletSpeed * DamageModefire;
	CurentBullet->Damage = GunComponent->Damage * DamageModefire;
	CurentBullet->Activate();

	

}

void ASP_Gun::ResetCanShoot()
{
	GunComponent->Owner->bCanShoot = true;

}

void ASP_Gun::Burst()
{
	GunComponent->Owner->bCanShoot = false;

	burstsMade++;

	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 5000, ECollisionChannel::ECC_Visibility);

	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	FVector ShootDirection = AimPoint - FirePoint->GetComponentLocation();

	SpawnBullet(AimPoint, FirePoint);

	

	GunComponent->CurrentAmmo--;
	hud->PlayerHudWidget->UpdateAmmoText(GunComponent->CurrentAmmo, GunComponent->ExtraAmmo);

	if (burstsMade < GunComponent->BurstAmount)
	{
		


		if (GunComponent->CurrentAmmo < 0)
		{
			
		}
		else
		{
			FTimerHandle GunTimerHandle;

			GetWorldTimerManager().SetTimer(GunTimerHandle, this, &ASP_Gun::Burst, GunComponent->TimeBetweenBurts, false);
		}



	}
	else
	{
		FTimerHandle GunTimerHandle;

		GetWorldTimerManager().SetTimer(GunTimerHandle, this, &ASP_Gun::ResetCanShoot, GunComponent->TimeBetweenShots, false);

	}
}

void ASP_Gun::FullAuto()
{
	GunComponent->Owner->bCanShoot = false;

	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 5000, ECollisionChannel::ECC_Visibility);

	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;



	SpawnBullet(AimPoint, FirePoint);

	GunComponent->CurrentAmmo--;


	hud->PlayerHudWidget->UpdateAmmoText(GunComponent->CurrentAmmo, GunComponent->ExtraAmmo);

	FTimerHandle GunTimerHandle;

	GetWorldTimerManager().SetTimer(GunTimerHandle, this, &ASP_Gun::ResetCanShoot, GunComponent->TimeBetweenShots, false);
}

void ASP_Gun::SemiAuto()
{
	GunComponent->Owner->bCanShoot = false;

	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 5000, ECollisionChannel::ECC_Visibility);

	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	SpawnBullet(AimPoint, FirePoint);

	GunComponent->CurrentAmmo--;


	hud->PlayerHudWidget->UpdateAmmoText(GunComponent->CurrentAmmo, GunComponent->ExtraAmmo);
}

void ASP_Gun::Charge()
{
	if (bHasStartedCharge == false)
	{
		hud->PlayerHudWidget->ChageChargeSliderVisibility(true);
		ChargeValue = 0;
		bHasStartedCharge = true;
	}
	else if (ChargeValue < MaxChargeValue)
	{
		ChargeValue += 0.1f;
	}
	hud->PlayerHudWidget->UpdateChargeSlider( ChargeValue / MaxChargeValue);

}

void ASP_Gun::ChargeRelease()
{
	GunComponent->Owner->bCanShoot = false;
	

	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 5000, ECollisionChannel::ECC_Visibility);

	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	if (ChargeValue < 1)
	{
		SpawnBullet(AimPoint, FirePoint);
	}
	else
	{
		SpawnBullet(AimPoint, FirePoint, ChargeValue);
	}

	ChargeValue = 0;

	GunComponent->CurrentAmmo--;
	bHasStartedCharge = false;
	hud->PlayerHudWidget->ChageChargeSliderVisibility(false);
	hud->PlayerHudWidget->UpdateChargeSlider(ChargeValue / MaxChargeValue);
	hud->PlayerHudWidget->UpdateAmmoText(GunComponent->CurrentAmmo, GunComponent->ExtraAmmo);


	FTimerHandle GunTimerHandle;

	GetWorldTimerManager().SetTimer(GunTimerHandle, this, &ASP_Gun::ResetCanShoot, GunComponent->TimeBetweenShots, false);
}

