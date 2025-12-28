#include "SP_HealthComponent.h"

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}
