#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"


class SPlayerHud : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SPlayerHud) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ASP_HUD>, OwningHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TWeakObjectPtr<class ASP_HUD> OwningHUD;



	void UpdateAmmoText(int current, int Extra);

	void UpdateHPPercent(float percent);

	void UpdateUltimatePercent(float percent);

	void UpdatePrimaryAbilityPercent(float percent);

	void UpdateElementalAbilityPercent(float percent);


	virtual bool SupportsKeyboardFocus() const override { return true; }

private:

	void SetSlateBrushes();

	FText GetCurrntAmmoText() const { return CurrntAmmoText; }
	FText GetExtraAmmoText() const { return ExtraAmmoText; }

	FSlateBrush GetHPBrush() const { return HPBrush; }

	
 
	UMaterialInterface* HealthBarMaterial = nullptr;
	UMaterialInstanceDynamic* HPMaterialInstance = nullptr;

	UMaterialInterface* UltimateMaterial = nullptr;
	UMaterialInstanceDynamic* UltimateMaterialInstance = nullptr;

	UMaterialInterface* PrimaryAbilityMaterial = nullptr;
	UMaterialInstanceDynamic* PrimaryAbilityMaterialInstance = nullptr;

	UMaterialInterface* ElementalAbilityMaterial = nullptr;
	UMaterialInstanceDynamic* ElementalAbilityMaterialInstance = nullptr;

	FSlateBrush HPBrush;
	FSlateBrush UltimateBrush;
	FSlateBrush PrimaryAbilityBrush;
	FSlateBrush ElementalAbilityBrush;

	FSlateBrush UltimateSliderBrush;
	FSlateBrush PrimaryAbilitySliderBrush;
	FSlateBrush ElementalAbilitySliderBrush;

	FText CurrntAmmoText;
	FText ExtraAmmoText;

	float UltimatePercent;
	float PrimaryAbilityPercent;
	float ElementalAbilityPercent;


};