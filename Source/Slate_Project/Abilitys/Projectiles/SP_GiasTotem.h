#pragma once 
#include "../SP_AbilityPlacable.h"
#include "SP_GiasTotem.generated.h"

class USphereComponent;
class ASPCharacter;
class UBuffDataAsset;
class UGiasBlesing;
class UBuffBase;


UCLASS()
class AGiasTotem : public AAbilityPlacable
{
	GENERATED_BODY()

public:

	AGiasTotem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* AouraBorder = nullptr;

	UFUNCTION()
	void OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Activate(FVector Location) override;

	void DeActivate() override;

	UPROPERTY(EditDefaultsOnly)
	UBuffDataAsset* OnEnterBuffToApply = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UBuffDataAsset* OnExitBuffToApply = nullptr;

private:

	TArray<ASPCharacter*> playerList;

	UBuffBase* OnEnternewBuff = nullptr;

	UBuffBase* OnExitnewBuff = nullptr;
};