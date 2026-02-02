#pragma once

#include "GameFramework/Actor.h"
#include "SP_WeaponBase.h"
#include "SP_MeleweaponBase.generated.h"

class ASPCharacter;
class ASP_HUD;
class UMeleWeaponComponent;
class UBoxComponent;
UCLASS()
class ASP_MeleWeapon : public AWeaponBase 
{

	GENERATED_BODY()
public:
	ASP_MeleWeapon();

	bool CanDamage = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root = nullptr;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	UBoxComponent* WeaponColider = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMeleWeaponComponent* WeaponComponent = nullptr;

	UPROPERTY(BlueprintReadWrite)
	ASPCharacter* player = nullptr;

	UFUNCTION()
	void UseMele();

	UFUNCTION()
	void ReleaseMele();



	UFUNCTION()
	void OnMeleeHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};