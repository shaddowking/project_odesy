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


	virtual bool SupportsKeyboardFocus() const override { return true; }

private:

	FSlateBrush HPBrush;

	FText GetCurrntAmmoText() const { return CurrntAmmoText; }
	FText GetExtraAmmoText() const { return ExtraAmmoText; }

	FSlateBrush GetHPBrush() const { return HPBrush; }
 
	UMaterialInterface* HealthBarMaterial = nullptr;
	UMaterialInstanceDynamic* MaterialInstance = nullptr;

	FText CurrntAmmoText;
	FText ExtraAmmoText;


};