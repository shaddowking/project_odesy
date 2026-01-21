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
	void UpdatePrimaryAbilityIcon(UTexture2D* icon);

	void UpdateElementalAbilityPercent(float percent);
	void UpdateElementAbilityIcon(UTexture2D* icon);

	void UpdateWeaponChargeSlider(float percent);
	void ChageChargeSliderVisibility(bool IsVisible);

	virtual bool SupportsKeyboardFocus() const override { return true; }

private:

	void SetSlateBrushes();

	FText GetCurrntAmmoText() const { return CurrntAmmoText; }
	FText GetExtraAmmoText() const { return ExtraAmmoText; }

	FSlateBrush GetHPBrush() const { return HPBrush; }

	EVisibility GetChargeWeaponSliderVisibility() const { return WeaponChargeSliderVisibility; }

	
 
	UMaterialInterface* HealthBarMaterial = nullptr;
	UMaterialInstanceDynamic* HPMaterialInstance = nullptr;

	UMaterialInterface* UltimateMaterial = nullptr;
	UMaterialInstanceDynamic* UltimateMaterialInstance = nullptr;

	UMaterialInterface* PrimaryAbilityMaterial = nullptr;
	UMaterialInstanceDynamic* PrimaryAbilityMaterialInstance = nullptr;

	UMaterialInterface* ElementalAbilityMaterial = nullptr;
	UMaterialInstanceDynamic* ElementalAbilityMaterialInstance = nullptr;

	UMaterialInterface* WeaponChargeMaterial = nullptr;
	UMaterialInstanceDynamic* WeaponChargeInstance = nullptr;

	FSlateBrush HPBrush;
	FSlateBrush UltimateBrush;
	FSlateBrush PrimaryAbilityBrush;
	FSlateBrush ElementalAbilityBrush;

	FSlateBrush UltimateSliderBrush;
	FSlateBrush PrimaryAbilitySliderBrush;
	FSlateBrush ElementalAbilitySliderBrush;

	FText CurrntAmmoText;
	FText ExtraAmmoText;
	FSlateBrush ChargeSliderBrush;

	EVisibility WeaponChargeSliderVisibility;

	float UltimatePercent;
	float PrimaryAbilityPercent;
	float ElementalAbilityPercent;


};