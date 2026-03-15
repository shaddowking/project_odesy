#include "SP_MeleweaponBase.h"
#include "Components/BoxComponent.h"
#include "SP_MeleWeaponComponent.h"
#include "SP_HealthComponent.h"
#include "Enemys/SP_EnemyBase.h"
#include "SP_Player.h"

ASP_MeleWeapon::ASP_MeleWeapon()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	WeaponColider = CreateDefaultSubobject<UBoxComponent>("WeaponColider");
	WeaponColider->SetupAttachment(Root);
	WeaponColider->OnComponentBeginOverlap.AddDynamic(this, &ASP_MeleWeapon::OnMeleeHit);

	WeaponComponent = CreateDefaultSubobject<UMeleWeaponComponent>("MeleeComponent");
	WeaponComponent->OnShoot.AddDynamic(this, &ASP_MeleWeapon::UseMele);
	WeaponComponent->OnRealese.AddDynamic(this, &ASP_MeleWeapon::ReleaseMele);
	WeaponComponent->OnActivate.AddDynamic(this, &ASP_MeleWeapon::Activate);
	WeaponComponent->OnDeactivate.AddDynamic(this, &ASP_MeleWeapon::Deactivate);
	WeaponComponent->OwningWeapon = this;

}

void ASP_MeleWeapon::UseMele()
{
	WeaponComponent->Owner->AnimateWeapon();
}

void ASP_MeleWeapon::ReleaseMele()
{
}

void ASP_MeleWeapon::Activate()
{
	SetActorHiddenInGame(false);
	WeaponColider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASP_MeleWeapon::Deactivate()
{
	SetActorHiddenInGame(true);
	WeaponColider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASP_MeleWeapon::OnMeleeHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != Owner && Cast<AEnemyBase>(OtherActor) && WeaponComponent->bIsUsingWeapon)
	{
		UHealthComponent* healthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
		if (healthComponent)
		{
			healthComponent->TakeDamage(WeaponComponent->CalculateDamage());
			healthComponent = nullptr;
		}
	}
}
