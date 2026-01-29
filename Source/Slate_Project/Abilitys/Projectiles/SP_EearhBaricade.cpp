#include "SP_EearhBaricade.h"
#include "../../SP_HealthComponent.h"

#include"Components/BoxComponent.h"

AEarthBaricade::AEarthBaricade()
{
	hpcomp = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	hpcomp->OnDamage.AddDynamic(this, &AEarthBaricade::OnBaricadeDamage);
	hpcomp->OnDeath.AddDynamic(this, &AEarthBaricade::OnBaricadeDeath);
	baricadeCollision = CreateDefaultSubobject<UBoxComponent>("baricadeCollition");
	baricadeCollision->SetupAttachment(Root);
}

void AEarthBaricade::OnBaricadeDamage()
{
}

void AEarthBaricade::OnBaricadeDeath()
{
	DeActivate();
}

void AEarthBaricade::Activate(FVector Location)
{
	Super::Activate(Location);
	baricadeCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

void AEarthBaricade::DeActivate()
{
	Super::DeActivate();
	baricadeCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}
