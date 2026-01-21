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

	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush HPImageBrush;
	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush UltimateImageBrush;
	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush PrimaryAbilityImageBrush;
	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush ElementalAbilityImageBrush;

	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush UISliderBrush;

	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush ShargeWeaponSlider;

	
};