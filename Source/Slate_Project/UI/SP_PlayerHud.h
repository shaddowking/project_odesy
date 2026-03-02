#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"

#include "SP_HUD.h"

#include "SP_BuffUI.h"

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
	void UpdateUltimateIcon(UTexture2D* icon);
	void UpdateUlitmateSliderColor(bool finished);

	void UpdatePrimaryAbilityPercent(float percent);
	void UpdatePrimaryAbilityIcon(UTexture2D* icon);

	void UpdateElementalAbilityPercent(float percent);
	void UpdateElementAbilityIcon(UTexture2D* icon);

	void UpdateChargeSlider(float percent);
	void ChageChargeSliderVisibility(bool IsVisible);

	void UpdateBaseTeleportVisibility(bool IsVisible)
	{
		if (IsVisible)
		{
			BaseTeleportVisibility = EVisibility::HitTestInvisible;
		}
		else
		{
			BaseTeleportVisibility = EVisibility::Collapsed;
		}
	}
	void UpdateBaseTelebortSlider(float percent);

	virtual bool SupportsKeyboardFocus() const override { return true; }

	void SetSlateBrushes();


private:


	FText GetCurrntAmmoText() const { return CurrntAmmoText; }
	FText GetExtraAmmoText() const { return ExtraAmmoText; }


	EVisibility GetChargeSliderVisibility() const { return ChargeSliderVisibility; }
	EVisibility GetBaseTeleportVisibility() const { return BaseTeleportVisibility; }
	UMaterialInstanceDynamic* CreateMateralInstance(UMaterialInterface* materialInterface) 
	{
		return OwningHUD->MakeMaterialInstance(materialInterface);

	}

 
	

	FSlateBrush HPBrush;
	FSlateBrush UltimateBrush;
	FSlateBrush PrimaryAbilityBrush;
	FSlateBrush ElementalAbilityBrush;

	FSlateBrush UltimateSliderBrush;
	FSlateBrush PrimaryAbilitySliderBrush;
	FSlateBrush ElementalAbilitySliderBrush;

	FVector4 Ultimatesliderfinish;
	FVector4 Ultimateslidercolor;

	FText CurrntAmmoText;
	FText ExtraAmmoText;
	FSlateBrush ChargeSliderBrush;

	EVisibility ChargeSliderVisibility;

	FSlateBrush BaseTeleportBrush;
	EVisibility BaseTeleportVisibility = EVisibility::Collapsed;

	float UltimatePercent;
	float PrimaryAbilityPercent;
	float ElementalAbilityPercent;


};