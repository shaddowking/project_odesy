#pragma once 

#include "Components/ActorComponent.h"

#include "OD_CompassindicatorCompenent.generated.h"

class UCompassIndicatorUI;
class UQuestIndicator;

UCLASS(meta = (BlueprintSpawnableComponent))
class UCompassIndicator : public UActorComponent 
{

	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, Category = "Indicator")
	bool bIsCompassInicator = false;
	UPROPERTY(EditAnywhere, Category = "Indicator")
	bool bIsWorldInicator = false;
	UPROPERTY(EditAnywhere, Category = "Indicator")
	bool bIsMapInicator = false;


	UPROPERTY(EditDefaultsOnly, Category = "Icon")
	FSlateBrush CompassIcon;

	

	UPROPERTY(BlueprintReadWrite)
	UQuestIndicator* createdQIndicator = nullptr;
	UPROPERTY(BlueprintReadWrite)
	UCompassIndicatorUI* CreatedCIndicator = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CompassIconTemplate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> QuestIconTemplate;

	

	

	void SetupUI();

};