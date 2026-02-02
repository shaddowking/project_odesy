#pragma once

#include "SP_WeaponComponent.h"
#include "SP_MeleWeaponComponent.generated.h"



UCLASS(meta = (BlueprintSpawnableComponent))
class UMeleWeaponComponent : public UWeaponBaseCompnent
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	bool bIsUsingWeapon = false;

};