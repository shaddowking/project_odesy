#pragma once 
#include "GameFramework/Actor.h"
#include "SP_ItemStruct.h"
#include "OD_ItemPickup.generated.h"

class UBoxComponent;


UCLASS()
class AItemPickup : public AActor
{
GENERATED_BODY()

public:

	AItemPickup();

	UPROPERTY(EditAnywhere)
	float PickupAmountMin = 1;

	UPROPERTY(EditAnywhere)
	float PickupAmountMax = 3;

	UPROPERTY(EditAnywhere)
	FItem pickupItem;

	bool bIsUsed = false;

	UFUNCTION()
	void OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	UBoxComponent* pickupCollision = nullptr;

	void ActivatPickup();

	void DeactivatePickup();

	UFUNCTION(BlueprintImplementableEvent)
	void BPDeactivet();

	UFUNCTION(BlueprintImplementableEvent)
	void BPActivet();
};