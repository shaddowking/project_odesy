#pragma once
#include "Blueprint/UserWidget.h"

#include "OD_QuestIndicator.generated.h"

class UGameplayStatics;

UCLASS()
class UQuestIndicator : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float MaxRange = 1000;

	UPROPERTY(BlueprintReadWrite)
	AActor* TrackingActor = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void SetupInicator(FSlateBrush indicator, AActor* tracking);

	UFUNCTION(BlueprintCallable)
	void UpdateWidgetClampValues(FVector2D ViewportSize, FVector2D IconSize, float ViewportSclae);

	UFUNCTION(BlueprintCallable)
	bool IsTargetLocationWithinScreenClamp(FVector Worldpos, float ViewportScale);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateWidgetLocation(bool OnScreen);

	UFUNCTION(BlueprintCallable)
	void UpdateMidpointPosandDirection(float ViewportScale);


	

	UPROPERTY(EditAnywhere)
	float Acuracy = 0.25;

	UPROPERTY(BlueprintReadWrite)
	FVector2D ScreenPosition;

	UPROPERTY(BlueprintReadWrite)
	FVector2D SavedViewportSize;
	UPROPERTY(BlueprintReadWrite)
	FVector2D ClampMin;
	UPROPERTY(BlueprintReadWrite)
	FVector2D ClampMax;

	UPROPERTY(BlueprintReadWrite)
	FVector2D widgetPos;
	UPROPERTY(BlueprintReadWrite)
	FVector MiddlePorint;

	UPROPERTY(BlueprintReadWrite)
	FVector ObjectDirection;
	UPROPERTY(BlueprintReadWrite)
	FVector MidPointTowardsObject;
	UPROPERTY(BlueprintReadWrite)
	FVector worldDirection;

	UPROPERTY(BlueprintReadWrite)
	FVector2D ScreenMiddle2D;
	UPROPERTY(BlueprintReadWrite)
	FVector2D RunAndRise;

	UPROPERTY(BlueprintReadWrite)
	float LineLengh;

	UPROPERTY(BlueprintReadWrite)
	FVector TargetLocation;
private:


};