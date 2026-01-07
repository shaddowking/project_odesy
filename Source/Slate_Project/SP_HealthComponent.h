#pragma once
#include "Components/ActorComponent.h"
#include "SP_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDeathSignature);

UCLASS(meta = (BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void TakeDamage(float Damage)
	{
		CurrentHealth -= Damage;
		LatestDamage = Damage;
		OnDamage.Broadcast();

		if (CurrentHealth <= 0.f)
		{
			CurrentHealth = 0.f;
			OnDeath.Broadcast();
		}
	}
	UFUNCTION(BlueprintCallable)
	void Heal(float HealValu)
	{
		CurrentHealth += HealValu;
		if (CurrentHealth > MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", UIMax = "500.0"))
	float MaxHealth = 100.f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float LatestDamage = 0.f;

	UPROPERTY(BlueprintAssignable)
	FHealthDeathSignature OnDeath;

	UPROPERTY(BlueprintAssignable)
	FHealthDeathSignature OnDamage;

};