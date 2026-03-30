#include "OD_OreBase.h"
#include "../SP_HealthComponent.h"
#include "../Inventory/OD_ItemPickup.h"

#include "Kismet/GameplayStatics.h"
#include "../SP_GameInstance.h"
#include "../WorldPlacables/OD_ExploreManager.h"

AOreBase::AOreBase()
{
	HPComp = CreateDefaultSubobject<UHealthComponent>("HPComponent");
	HPComp->OnDeath.AddDynamic(this, &AOreBase::OnDestroyd);
	HPComp->OnDamage.AddDynamic(this, &AOreBase::OnDamaged);

}

void AOreBase::BeginPlay()
{
	GI = Cast<USPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
}

void AOreBase::Activate()
{
	SetActorHiddenInGame(false);
	BPActivate();
	HPComp->Heal(HPComp->MaxHealth);

}

void AOreBase::Deactivate()
{
	SetActorHiddenInGame(true);
	BPDestroyd();
}

void AOreBase::OnDamaged()
{
	
}

void AOreBase::OnDestroyd()
{
	
	newpickup = GI->ExploreManager->GetPickup(DesierdItem, this);
	
	if (newpickup)
	{
		newpickup->ActivatPickup();
		newpickup->SetActorLocation(GetActorLocation());
	}
	
	Deactivate();
}
