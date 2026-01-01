#include "SP_EnemyBase.h"
#include "../SP_HealthComponent.h"

AEnemyBase::AEnemyBase()
{
	HPComp = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HPComp->OnDamage.AddDynamic(this, &AEnemyBase::OnDamage);
	HPComp->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
}

void AEnemyBase::OnDamage()
{
}

void AEnemyBase::OnDeath()
{
	BPOnDeath();
}
