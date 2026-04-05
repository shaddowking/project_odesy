#pragma once 

#include "GameFramework/HUD.h"
#include "SP_HUD.generated.h"

class ASP_GameMode;
class UBuffList;
class ASPCharacter;
class UCompasUI;
class UInventoryAdd;
class UMinimap;
UCLASS()
class ASP_HUD : public AHUD {
	GENERATED_BODY()

protected:
	

	virtual void BeginPlay() override;

public:

	ASPCharacter* Player;
	
	UPROPERTY(BlueprintReadWrite)
	UMinimap* Minimap = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> buffListTemplate;
	UBuffList* buffList = nullptr;
	
	TSharedPtr<class SPlayerHud> PlayerHudWidget;
	TSharedPtr<class SWidget> PHudWidgetContainer;

	TSharedPtr<class SSubclassMenu> SubclassMenu;
	TSharedPtr<class SWidget> PSubclassMenuContainer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CompassTemplate;
	UCompasUI* CompassUI = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InventoryAddTemplate;
	UInventoryAdd* InventoryAddUI = nullptr;

	void CreateSubclassMenu(ASPCharacter* player);

	void ShowSubclassMenu();
	void HideSubclassMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void SetupMapMarker(FSlateBrush icon,AActor* target,bool HideWhenNotVisible);

	UFUNCTION(BlueprintImplementableEvent)
	UMaterialInstanceDynamic* MakeMaterialInstance(UMaterialInterface* MInterface);
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
	FSlateBrush UltimateSliderBrush;

	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FVector4 UltimateSliderFinish;

	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FVector4 UltimateSlidercollor;

	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush ShargeWeaponSlider;

	UPROPERTY(EditDefaultsOnly, Category = "Brush")
	FSlateBrush beseTeleportSlider;

	UPROPERTY()
	UMaterialInstanceDynamic* HPMaterialInstance = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* UltimateMaterialInstance = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* PrimaryAbilityMaterialInstance = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* ElementalAbilityMaterialInstance = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* ChargeSliderMaterialInstance = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* BaseTeleportMaterialInstance = nullptr;
};