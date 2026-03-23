#include "SP_EnemyBase.h"
#include "../SP_HealthComponent.h"
#include "../Map/OD_CompassindicatorCompenent.h"

AEnemyBase::AEnemyBase()
{
	HPComp = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HPComp->OnDamage.AddDynamic(this, &AEnemyBase::OnDamage);
	HPComp->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
	compassIndicator = CreateDefaultSubobject<UCompassIndicator>("CompassIndicator");
}

void AEnemyBase::OnDamage()
{
}

void AEnemyBase::OnDeath()
{
	BPOnDeath();
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	compassIndicator->SetupUI();
}
