#pragma once
#include "GameFramework/Character.h"
#include "SP_EnemyBase.generated.h"

class UHealthComponent;


UCLASS()
class AEnemyBase : public ACharacter {
	GENERATED_BODY()

public:

	AEnemyBase();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UHealthComponent* HPComp = nullptr;

	UFUNCTION()
	void OnDamage();

	UFUNCTION()
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void BPOnDeath();
};