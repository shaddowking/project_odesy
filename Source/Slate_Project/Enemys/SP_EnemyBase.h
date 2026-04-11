#pragma once
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"

#include "SP_EnemyBase.generated.h"

class UHealthComponent;
class UblackboardComponent;
class USphereComponent;


UCLASS()
class AEnemyBase : public ACharacter {
	GENERATED_BODY()

public:

	AEnemyBase();

	void FieldOfViewCheck();

	void Tick(float DeltaTime) override;

	//FOV

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FOV")
	float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FOV")
	float angle;

	UPROPERTY()
	TArray<AActor*> targetList;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FOV")
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY()
	AActor* TargetActor = nullptr;

	float bestdistance;
	UPROPERTY()
	UWorld* World = nullptr;
	//---


	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UHealthComponent* HPComp = nullptr;

	UFUNCTION()
	void OnDamage();

	UFUNCTION()
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void BPOnDeath();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BPOnDamage();

	UFUNCTION()
	void BeginPlay()override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardData* Blackboard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	float MelleDamage = 10;

	bool bIsDead = false;

private:

	FVector MyLocation;
	FVector TargetLocation;

	float InterpSpeed = 5.0f;

	FRotator TargetRotation;

	FRotator NewRotation;
};