#pragma once
#include "GameFramework/Actor.h"
#include "../Inventory/SP_ItemStruct.h"

#include "OD_OreBase.generated.h"

class UHealthComponent;
class AItemPickup;
class USPGameInstance;

UCLASS()
class AOreBase : public AActor
{

	GENERATED_BODY()

public:

	AOreBase();

	void BeginPlay()override;

	UPROPERTY()
	USPGameInstance* GI = nullptr;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AItemPickup> pickupTemplate;

	UPROPERTY(EditAnywhere)
	FItem DesierdItem;

	UPROPERTY(EditAnywhere)
	UHealthComponent* HPComp = nullptr;

	void Activate();
	void Deactivate();

	UFUNCTION()
	void OnDamaged();

	UFUNCTION()
	void OnDestroyd();

	UFUNCTION(BlueprintImplementableEvent)
	void BPActivate();

	UFUNCTION(BlueprintImplementableEvent)
	void BPDestroyd();

private:

	UPROPERTY()
	AItemPickup* newpickup = nullptr;

};