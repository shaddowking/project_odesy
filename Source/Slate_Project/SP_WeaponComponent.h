#pragma once
#include "Components/ActorComponent.h"
#include "SP_WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSPWeaponSigniture);

class ASPCharacter;


UCLASS()
class UWeaponBaseCompnent : public UActorComponent 
{
GENERATED_BODY()

public:

	virtual void UseWeapon(FVector origin, FVector Forward)
	{
		ViewOrigin = origin;
		ViewForward = Forward;
		OnShoot.Broadcast();
	}

	virtual void RealeseWeapon()
	{
		OnRealese.Broadcast();
	}

	void ActivateWeapon() 
	{
		OnActivate.Broadcast();
	}

	void DeactivateWeapon() 
	{
		OnDeactivate.Broadcast();
	}

	UPROPERTY(BlueprintAssignable)
	FSPWeaponSigniture OnShoot;
	UPROPERTY(BlueprintAssignable)
	FSPWeaponSigniture OnRealese;
	UPROPERTY(BlueprintAssignable)
	FSPWeaponSigniture OnActivate;
	UPROPERTY(BlueprintAssignable)
	FSPWeaponSigniture OnDeactivate;



	UPROPERTY(BlueprintReadOnly)
	FVector ViewOrigin;
	UPROPERTY(BlueprintReadOnly)
	FVector ViewForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float Damage = 10;

	UPROPERTY(BlueprintReadWrite)
	ASPCharacter* Owner = nullptr;

};