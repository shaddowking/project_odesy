#include "SP_PlayerHud.h"
#include "SP_HUD.h"

#include "UObject/ConstructorHelpers.h"


#define LOCTEXT_NAMESPACE "PlayerHud"

void SPlayerHud::Construct(const FArguments& InArgs) 
{
	OwningHUD = InArgs._OwningHUD;

	

	SetSlateBrushes();

	FSlateFontInfo CurrentAmmoTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	CurrentAmmoTextStyle.Size = 30.f;

	FSlateFontInfo ExtraAmmoTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ExtraAmmoTextStyle.Size = 25.f;

	CurrntAmmoText = FText::FromString(TEXT( "0"));
	ExtraAmmoText = FText::FromString(TEXT("0"));

	ChildSlot
		[
			SNew(SOverlay) 
			+ SOverlay::Slot()
			.Padding(FMargin(80.f,100.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			[
				SNew(STextBlock).Text(this, &SPlayerHud::GetCurrntAmmoText).ColorAndOpacity(FColor::Black).Font(CurrentAmmoTextStyle)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(40.f, 70.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			[
				SNew(STextBlock).Text(this, &SPlayerHud::GetExtraAmmoText).ColorAndOpacity(FColor::Black).Font(ExtraAmmoTextStyle)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(40.f, 40.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			[
				SNew(SImage).Image(&HPBrush)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(250.f, 150.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			[
				SNew(SImage)
					.Image(&UltimateSliderBrush)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(250.f, 40.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			[					
				SNew(SImage)
					.Image(&PrimaryAbilityBrush)
					
			]
			+ SOverlay::Slot()
			.Padding(FMargin(250.f, 40.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			[					
				SNew(SImage)
					.Image(&PrimaryAbilitySliderBrush)
			]
			
			+ SOverlay::Slot()
			.Padding(FMargin(350.f, 40.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			[					
				SNew(SImage)
					.Image(&ElementalAbilityBrush)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(350.f, 40.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			[					
				SNew(SImage)
					.Image(&ElementalAbilitySliderBrush)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(400.f, 0.f))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SNew(SImage).Image(&ChargeSliderBrush).Visibility(this, &SPlayerHud::GetChargeSliderVisibility)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(0.f, 0.f))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
			]
			
			

		];

}



void SPlayerHud::UpdateAmmoText(int current, int Extra)
{
	CurrntAmmoText = FText::FromString(FString::FromInt(current));
	ExtraAmmoText = FText::FromString(FString::FromInt(Extra));
}

void SPlayerHud::UpdateHPPercent(float percent)
{
	HPMaterialInstance->SetScalarParameterValue("Percentage", percent);
}

void SPlayerHud::UpdateUltimatePercent(float percent)
{
	UltimatePercent = percent;
	if (UltimateMaterialInstance)
	{
		UltimateMaterialInstance->SetScalarParameterValue("Percent", percent);

	}

}

void SPlayerHud::UpdateUltimateIcon(UTexture2D* icon)
{
	UltimateBrush.SetResourceObject(icon);
}

void SPlayerHud::UpdateUlitmateSliderColor(bool finished)
{
	if (finished)
	{
		if (UltimateMaterialInstance)
		{
			
			UltimateMaterialInstance->SetVectorParameterValue("SliderCollor", Ultimatesliderfinish);

		}
	}
	else
	{
		if (UltimateMaterialInstance)
		{
			UltimateMaterialInstance->SetVectorParameterValue("SliderCollor",Ultimateslidercolor);

		}
	}
}

void SPlayerHud::UpdatePrimaryAbilityPercent(float percent)
{
	PrimaryAbilityPercent = percent;
	if (PrimaryAbilityMaterialInstance)
	{
		PrimaryAbilityMaterialInstance->SetScalarParameterValue("Percent", percent);

	}
}

void SPlayerHud::UpdatePrimaryAbilityIcon(UTexture2D* icon)
{
	PrimaryAbilityBrush.SetResourceObject(icon);
}

void SPlayerHud::UpdateElementalAbilityPercent(float percent)
{
	ElementalAbilityPercent = percent;
	if (ElementalAbilityMaterialInstance)
	{
		ElementalAbilityMaterialInstance->SetScalarParameterValue("Percent", percent);

	}
}

void SPlayerHud::UpdateElementAbilityIcon(UTexture2D* icon)
{
	ElementalAbilityBrush.SetResourceObject(icon);
}

void SPlayerHud::UpdateChargeSlider(float percent)
{
	if (ChargeSliderMaterialInstance)
	{
		ChargeSliderMaterialInstance->SetScalarParameterValue("Percent", percent);
	}
}

void SPlayerHud::ChageChargeSliderVisibility(bool IsVisible)
{
	

	if (IsVisible)
	{
		ChargeSliderVisibility = EVisibility::HitTestInvisible;
	}
	else
	{
		ChargeSliderVisibility = EVisibility::Collapsed;
	}



}





void SPlayerHud::SetSlateBrushes()
{
	//HP-------
	HPBrush = OwningHUD->HPImageBrush;

	HealthBarMaterial = Cast<UMaterialInterface>(HPBrush.GetResourceObject());
	HPMaterialInstance = UMaterialInstanceDynamic::Create(HealthBarMaterial, OwningHUD->GetWorld()->GetFirstPlayerController());
	HPBrush.SetResourceObject(HPMaterialInstance);
	//---------
	//Abilitys-

	Ultimateslidercolor = OwningHUD->UltimateSlidercollor;
	Ultimatesliderfinish = OwningHUD->UltimateSliderFinish;

	UltimateBrush = OwningHUD->UltimateImageBrush;
	UltimateSliderBrush = OwningHUD->UltimateSliderBrush;

	UltimateMaterial = Cast<UMaterialInterface>(UltimateSliderBrush.GetResourceObject());
	UltimateMaterialInstance = UMaterialInstanceDynamic::Create(UltimateMaterial, OwningHUD->GetWorld()->GetFirstPlayerController());
	UltimateSliderBrush.SetResourceObject(UltimateMaterialInstance);

	
	PrimaryAbilityBrush = OwningHUD->PrimaryAbilityImageBrush;
	PrimaryAbilitySliderBrush = OwningHUD->UISliderBrush;

	PrimaryAbilityMaterial = Cast<UMaterialInterface>(PrimaryAbilitySliderBrush.GetResourceObject());
	PrimaryAbilityMaterialInstance = UMaterialInstanceDynamic::Create(PrimaryAbilityMaterial, OwningHUD->GetWorld()->GetFirstPlayerController());
	PrimaryAbilitySliderBrush.SetResourceObject(PrimaryAbilityMaterialInstance);


	ElementalAbilityBrush = OwningHUD->ElementalAbilityImageBrush;
	ElementalAbilitySliderBrush = OwningHUD->UISliderBrush;

	ElementalAbilityMaterial = Cast<UMaterialInterface>(ElementalAbilitySliderBrush.GetResourceObject());
	ElementalAbilityMaterialInstance = UMaterialInstanceDynamic::Create(ElementalAbilityMaterial, OwningHUD->GetWorld()->GetFirstPlayerController());
	ElementalAbilitySliderBrush.SetResourceObject(ElementalAbilityMaterialInstance);

	//---------
	//Weapon

	ChargeSliderBrush = OwningHUD->ShargeWeaponSlider;

	ChargeSliderMaterial = Cast<UMaterialInterface>(ChargeSliderBrush.GetResourceObject());
	ChargeSliderMaterialInstance = UMaterialInstanceDynamic::Create(ChargeSliderMaterial, OwningHUD->GetWorld()->GetFirstPlayerController());
	ChargeSliderBrush.SetResourceObject(ChargeSliderMaterialInstance);


}



#undef LOCTEXT_NAMESPACE