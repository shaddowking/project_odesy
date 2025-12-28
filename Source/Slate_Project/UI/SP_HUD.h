#pragma once 

#include "GameFramework/HUD.h"
#include "SP_HUD.generated.h"

class ASP_GameMode;

UCLASS()
class ASP_HUD : public AHUD {
	GENERATED_BODY()

protected:
	

	virtual void BeginPlay() override;

public:
	TSharedPtr<class SPlayerHud> PlayerHudWidget;
	TSharedPtr<class SWidget> PHudWidgetContainer;

	UFUNCTION(BlueprintCallable)
	void EditorUpdateAmmoTexts(int current, int extra);

	UPROPERTY(EditAnywhere)
	FSlateBrush HPImageBrush;


	
};