#pragma once
#include "Components/ActorComponent.h"

#include "SP_Player.h"
#include "Buffes/SP_BuffeBase.h"
#include "SP_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDeathSignature);

class ASPCharacter;
class UBuffBase;

UCLASS(meta = (BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	float CalculateDamage(float StartDamage)
	{
		float result = StartDamage;
		if (player)
		{
			for (UBuffBase* buff : player->PlayerBuffs)
			{
				result = result * buff->BuffDefenceCalculation(player);
			}
		}
		
		

		return result;

	}

	void TakeDamage(float Damage)
	{
		
		CurrentHealth -= CalculateDamage(Damage);
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

	ASPCharacter* player = nullptr;

};