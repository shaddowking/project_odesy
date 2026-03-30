#include "OD_ExploreManager.h"
#include "../Inventory/OD_ItemPickup.h"
#include "OD_OreBase.h"
#include "Kismet/GameplayStatics.h"
#include "../SP_GameInstance.h"

void AExploreManager::BeginPlay()
{
    Super::BeginPlay();

    USPGameInstance* GI = Cast<USPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    GI->ExploreManager = this;
    GI = nullptr;
}

AItemPickup* AExploreManager::GetPickup(FItem desierdPickup, AOreBase* currentOre)
{
    curerntPickup = nullptr;
    
    for (AItemPickup* pickup : pickupPool) 
    {
        if (pickup->pickupItem == desierdPickup && pickup->bIsUsed == false)
        {
            curerntPickup = pickup;
            break;
        }
    }
    if (curerntPickup == nullptr)
    {
        curerntPickup = AddNewpickup(currentOre->pickupTemplate,currentOre->GetActorLocation());
    }

    curerntPickup->bIsUsed = true;
    

    return curerntPickup;
}

AItemPickup* AExploreManager::AddNewpickup(TSubclassOf<AItemPickup> newpickup, FVector position)
{
    NewPickup = nullptr;

    NewPickup = GetWorld()->SpawnActor<AItemPickup>(newpickup,position,FRotator::ZeroRotator);
    pickupPool.Add(NewPickup);

    return NewPickup;
}

void AExploreManager::Activate()
{
    for(AOreBase* ore : createdOreList)
    {
        ore->Activate();
    }
   
}

void AExploreManager::Deactivate()
{
    for (AOreBase* ore : createdOreList)
    {
        ore->Deactivate();
    }
    for (AItemPickup* pickup : pickupPool)
    {
        pickup->DeactivatePickup();
    }
}
