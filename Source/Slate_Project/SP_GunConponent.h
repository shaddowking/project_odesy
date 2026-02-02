#pragma once
#include "Components/ActorComponent.h"
#include "SP_WeaponComponent.h"
#include "SP_GunConponent.generated.h"



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
class USP_GunComponent : public UWeaponBaseCompnent {
	GENERATED_BODY()
public:

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun Stats")
	EGunType Guntype = EGunType::FullAuto;

	


	UPROPERTY(BlueprintReadOnly)
	ASP_Gun* OwningGun = nullptr;


	

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
	float BulletSpeed = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	int BurstAmount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float TimeBetweenBurts = 0.1;
};