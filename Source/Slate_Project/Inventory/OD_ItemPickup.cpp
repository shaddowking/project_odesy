#include "OD_ItemPickup.h"
#include "../SP_Player.h"
#include "Components/BoxComponent.h"
#include "SP_InventoryComponent.h"
#include "Math/UnrealMathUtility.h"


AItemPickup::AItemPickup()
{
	pickupCollision = CreateDefaultSubobject<UBoxComponent>("pickupCollision");

	pickupCollision->SetupAttachment(RootComponent);
	pickupCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemPickup::OnPickup);
}

void AItemPickup::OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASPCharacter* player = Cast<ASPCharacter>(OtherActor);
	if (player)
	{
		player->invertoryComponent->AddItemInInventory(pickupItem, FMath::RandRange(PickupAmountMin,PickupAmountMax));
		player = nullptr;
	}
	DeactivatePickup();
}

void AItemPickup::ActivatPickup()
{
	
	bIsUsed = true;
	SetActorHiddenInGame(false);
	pickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BPActivet();
	
}

void AItemPickup::DeactivatePickup()
{
	bIsUsed = false;
	SetActorHiddenInGame(true);
	pickupCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BPDeactivet();
}
