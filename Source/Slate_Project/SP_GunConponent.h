#pragma once
#include "Components/ActorComponent.h"
#include "SP_GunConponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSPGunSigniture);


class ASPCharacter;
class ASP_Gun;

UENUM(BlueprintType)
enum class EGunType : uint8
{
	FullAuto,
	SemiAuto,
	Burst,
	Charge
};

UCLASS(meta = (BlueprintSpawnableComponent))
class USP_GunComponent : public UActorComponent {
	GENERATED_BODY()
public:

	void FireGun(FVector origin, FVector Forward)
	{
		ViewOrigin = origin;
		ViewForward = Forward;
		OnShoot.Broadcast();
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun Stats")
	EGunType Guntype = EGunType::FullAuto;

	UPROPERTY(BlueprintReadWrite)
	ASPCharacter* Owner = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FVector ViewOrigin;
	UPROPERTY(BlueprintReadOnly)
	FVector ViewForward;

	UPROPERTY(BlueprintReadOnly)
	ASP_Gun* OwningGun = nullptr;


	UPROPERTY(BlueprintAssignable)
	FSPGunSigniture OnShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	float MaxAmmo = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float ExtraAmmo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float RelodeTime = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float GunDamage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float BulletSpeed = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	int BurstAmount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float TimeBetweenBurts = 0.1;
};