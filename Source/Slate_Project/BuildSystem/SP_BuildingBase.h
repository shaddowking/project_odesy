#pragma once 

#include "GameFramework/Actor.h"
#include "../Inventory/SP_ItemStruct.h"
#include "SP_BuildingBase.generated.h"

class UInteractionComponent;
class UBoxComponent;
class UBuildingUI;


UCLASS()
class ABuildingbase : public AActor 
{
GENERATED_BODY()

private:

	UPROPERTY()
	UBuildingUI* createdUI = nullptr;

public:

	void BeginPlay()override;


	ABuildingbase();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> BuildingUITemplate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BuildingCollision = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere)
	UInteractionComponent* interactComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FItem cost;

	UPROPERTY(BlueprintReadOnly)
	bool BIsGhost = false;

	UFUNCTION()
	virtual void OnInteract();

	UFUNCTION(BlueprintImplementableEvent)
	void SetGhostMaterial();

	UFUNCTION(BlueprintImplementableEvent)
	void SetCantBuildMaterial();

	virtual void ActivateBuilding();

	UFUNCTION(BlueprintImplementableEvent)
	void BPActivate();

	virtual void DeActivateBuilding();

	UFUNCTION(BlueprintImplementableEvent)
	void BPDeActivate();

	virtual void BuildingCreated();

};