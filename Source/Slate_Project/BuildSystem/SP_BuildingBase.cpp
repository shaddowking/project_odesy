#include "SP_BuildingBase.h"
#include "Components/BoxComponent.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "../UI/OD_BuildingUI.h"

#include "../OD_InteractionSystemComponent.h"




void ABuildingbase::BeginPlay()
{
	Super::BeginPlay();
	if (BuildingUITemplate && BIsGhost == false)
	{
		createdUI = CreateWidget<UBuildingUI>(GetWorld(), BuildingUITemplate);
		createdUI->AddToViewport();
		createdUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

ABuildingbase::ABuildingbase()
{
	interactComponent = CreateDefaultSubobject<UInteractionComponent>("interactComponent");
	interactComponent->OnInteracted.AddDynamic(this, &ABuildingbase::OnInteract);
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	BuildingCollision = CreateDefaultSubobject<UBoxComponent>("BuildingCollision");
	BuildingCollision->SetupAttachment(Root);
}

void ABuildingbase::OnInteract()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.0f,
		FColor::Green,
		TEXT("Interact")
	);
	//Make UI visible
	createdUI->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
}

void ABuildingbase::ActivateBuilding()
{
	BPActivate();
	SetActorHiddenInGame(false);
}

void ABuildingbase::DeActivateBuilding()
{
	BPDeActivate();
	SetActorHiddenInGame(true);
}

void ABuildingbase::BuildingCreated()
{
	ActivateBuilding();
	createdUI->InitializeBuildingUI();

}
