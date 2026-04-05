#pragma once 

#include "Components/ActorComponent.h"

#include "OD_CompassindicatorCompenent.generated.h"

class UCompassIndicatorUI;
class UQuestIndicator;
class UMapMarker;



UCLASS(meta = (BlueprintSpawnableComponent))
class UCompassIndicator : public UActorComponent 
{

	GENERATED_BODY()

public:

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DeactivateIndicator();
	UFUNCTION(BlueprintCallable)
	void ActivateIndicator();


	UPROPERTY(EditAnywhere, Category = "Indicator")
	bool bIsCompassInicator = false;
	UPROPERTY(EditAnywhere, Category = "Indicator")
	bool bIsWorldInicator = false;
	UPROPERTY(EditAnywhere, Category = "Indicator")
	bool bIsMapInicator = false;

	UPROPERTY()
	AActor* target = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Icon")
	FSlateBrush CompassIcon;

	UPROPERTY(EditAnywhere, Category = "Minimap")
	bool bHidewhenOffScreen = true;

	UPROPERTY(BlueprintReadWrite)
	UQuestIndicator* createdQIndicator = nullptr;
	UPROPERTY(BlueprintReadWrite)
	UCompassIndicatorUI* CreatedCIndicator = nullptr;
	UPROPERTY(BlueprintReadWrite)
	UMapMarker* CreatedMIndicator = nullptr;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CompassIconTemplate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> QuestIconTemplate;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MapIconTemplate;

	

	

	void SetupUI();

};