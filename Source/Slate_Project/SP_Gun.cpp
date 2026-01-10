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
}

void ASP_Gun::BeginPlay()
{
	Super::BeginPlay();
	GunComponent->CurrentAmmo = GunComponent->MaxAmmo;
	GunComponent->OwningGun = this;
	hud = Cast<ASP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	//player = GunComponent->Owner;
	//int test = player->ProjectilePool.Num();
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

void ASP_Gun::SpawnBullet(FVector AimPoint, USceneComponent* GunFirePoint)
{

	FVector ShootDirection = AimPoint - GunFirePoint->GetComponentLocation();



	AProjectile* CurentBullet = player->GetNextAvalableProjectile();

	CurentBullet->SetActorLocationAndRotation(GunFirePoint->GetComponentLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

	CurentBullet->Speed = GunComponent->BulletSpeed;
	CurentBullet->Activate();

	

}

void ASP_Gun::ResetCanShoot()
{
	GunComponent->Owner->bCanShoot = true;

}

void ASP_Gun::Burst()
{
	burstsMade++;

	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 5000, ECollisionChannel::ECC_Visibility);

	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	FVector ShootDirection = AimPoint - FirePoint->GetComponentLocation();


	AProjectile* CurentBullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, FirePoint->GetComponentLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

	AProjectile* Bullet = Cast<AProjectile>(CurentBullet);
	Bullet->Speed = GunComponent->BulletSpeed;

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
	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 5000, ECollisionChannel::ECC_Visibility);

	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	SpawnBullet(AimPoint, FirePoint);

	GunComponent->CurrentAmmo--;


	hud->PlayerHudWidget->UpdateAmmoText(GunComponent->CurrentAmmo, GunComponent->ExtraAmmo);
}

void ASP_Gun::Charge()
{
}

