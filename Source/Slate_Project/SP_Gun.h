#pragma once 
#include "GameFramework/Actor.h"

#include "SP_WeaponBase.h"
#include "SP_Gun.generated.h"

class USP_GunComponent;
class AProjectile;
class ASPCharacter;
class ASP_HUD;



UCLASS()
class ASP_Gun : public AWeaponBase {
	GENERATED_BODY()
public:

	ASP_Gun();

	void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* FirePoint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USP_GunComponent* GunComponent = nullptr;

	UPROPERTY(BlueprintReadWrite)
	ASPCharacter* player = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;


	UFUNCTION()
	void GunFire();

	UFUNCTION()
	void GunRealese();

	void SpawnBullet(FVector AimPoint, USceneComponent* GunFirePoint,float DamageModefire = 1);



	UPROPERTY(BlueprintReadOnly)
	int burstsMade;

	void ResetCanShoot();

private:

	ASP_HUD* hud = nullptr;

	void Burst();

	void FullAuto();
	void SemiAuto();
	void Charge();
	void ChargeRelease();

	bool bHasStartedCharge = false;
	float ChargeValue = 1;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAcces = "true"))
	float MaxChargeValue = 2;
};