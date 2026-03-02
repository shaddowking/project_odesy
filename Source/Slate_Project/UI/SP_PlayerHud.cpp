#include "SP_PlayerHud.h"
#include "SP_HUD.h"

#include "UObject/ConstructorHelpers.h"


#define LOCTEXT_NAMESPACE "PlayerHud"

void SPlayerHud::Construct(const FArguments& InArgs) 
{
	OwningHUD = InArgs._OwningHUD;

	//HPBrush = OwningHUD->HPImageBrush;

	Ultimateslidercolor = OwningHUD->UltimateSlidercollor;
	Ultimatesliderfinish = OwningHUD->UltimateSliderFinish;

	UltimateBrush = OwningHUD->UltimateImageBrush;
	//UltimateSliderBrush = OwningHUD->UltimateSliderBrush;

	PrimaryAbilityBrush = OwningHUD->PrimaryAbilityImageBrush;
	//PrimaryAbilitySliderBrush = OwningHUD->UISliderBrush;

	ElementalAbilityBrush = OwningHUD->ElementalAbilityImageBrush;
	//ElementalAbilitySliderBrush = OwningHUD->UISliderBrush;

	//ChargeSliderBrush = OwningHUD->ShargeWeaponSlider;

	
	//ERROR IN FUNCTION
	//SetSlateBrushes();
	//__________________
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
			.Padding(FMargin(400.f, 400.f))
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
			+ SOverlay::Slot()
			.Padding(FMargin(0.f, 0.f))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage).Image(&BaseTeleportBrush).Visibility(this, &SPlayerHud::GetBaseTeleportVisibility)
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
	if (OwningHUD->HPMaterialInstance)
	{
		OwningHUD->HPMaterialInstance->SetScalarParameterValue("Percentage", percent);
	}
	
}

void SPlayerHud::UpdateUltimatePercent(float percent)
{
	UltimatePercent = percent;
	if (OwningHUD->UltimateMaterialInstance)
	{
		OwningHUD->UltimateMaterialInstance->SetScalarParameterValue("Percent", percent);

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
		if (OwningHUD->UltimateMaterialInstance)
		{
			
			OwningHUD->UltimateMaterialInstance->SetVectorParameterValue("SliderCollor", Ultimatesliderfinish);

		}
	}
	else
	{
		if (OwningHUD->UltimateMaterialInstance)
		{
			OwningHUD->UltimateMaterialInstance->SetVectorParameterValue("SliderCollor",Ultimateslidercolor);

		}
	}
}

void SPlayerHud::UpdatePrimaryAbilityPercent(float percent)
{
	PrimaryAbilityPercent = percent;
	if (OwningHUD->PrimaryAbilityMaterialInstance)
	{
		OwningHUD->PrimaryAbilityMaterialInstance->SetScalarParameterValue("Percent", percent);

	}
}

void SPlayerHud::UpdatePrimaryAbilityIcon(UTexture2D* icon)
{
	PrimaryAbilityBrush.SetResourceObject(icon);
}

void SPlayerHud::UpdateElementalAbilityPercent(float percent)
{
	ElementalAbilityPercent = percent;
	if (OwningHUD->ElementalAbilityMaterialInstance)
	{
		OwningHUD->ElementalAbilityMaterialInstance->SetScalarParameterValue("Percent", percent);

	}
}

void SPlayerHud::UpdateElementAbilityIcon(UTexture2D* icon)
{
	ElementalAbilityBrush.SetResourceObject(icon);
}

void SPlayerHud::UpdateChargeSlider(float percent)
{
	if (OwningHUD->ChargeSliderMaterialInstance)
	{
		OwningHUD->ChargeSliderMaterialInstance->SetScalarParameterValue("Percent", percent);
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




void SPlayerHud::UpdateBaseTelebortSlider(float percent)
{
	if (OwningHUD->BaseTeleportMaterialInstance)
	{
		OwningHUD->BaseTeleportMaterialInstance->SetScalarParameterValue("Percentage", percent);
	}
}

//ERROR HAPENING IN MATERIAL INSTANCE CREATION
void SPlayerHud::SetSlateBrushes()
{
	UMaterialInterface* MInterface = nullptr;
	
	//HP-------

	MInterface = Cast<UMaterialInterface>(OwningHUD->HPImageBrush.GetResourceObject());
	OwningHUD->HPMaterialInstance = UMaterialInstanceDynamic::Create(MInterface, OwningHUD->GetWorld()->GetFirstPlayerController());
	HPBrush.SetResourceObject(OwningHUD->HPMaterialInstance);
	HPBrush.ImageSize = OwningHUD->HPImageBrush.ImageSize;
	HPBrush.TintColor = OwningHUD->HPImageBrush.TintColor;

	MInterface = Cast<UMaterialInterface>(OwningHUD->beseTeleportSlider.GetResourceObject());
	OwningHUD->BaseTeleportMaterialInstance = UMaterialInstanceDynamic::Create(MInterface, OwningHUD->GetWorld()->GetFirstPlayerController());
	BaseTeleportBrush.SetResourceObject(OwningHUD->BaseTeleportMaterialInstance);
	BaseTeleportBrush.ImageSize = OwningHUD->beseTeleportSlider.ImageSize;
	BaseTeleportBrush.TintColor = OwningHUD->beseTeleportSlider.TintColor;
	//---------
	//Abilitys-
	
	

	MInterface = Cast<UMaterialInterface>(OwningHUD->UltimateSliderBrush.GetResourceObject());
	OwningHUD->UltimateMaterialInstance = UMaterialInstanceDynamic::Create(MInterface, OwningHUD->GetWorld()->GetFirstPlayerController());
	UltimateSliderBrush.SetResourceObject(OwningHUD->UltimateMaterialInstance);
	UltimateSliderBrush.ImageSize = OwningHUD->UltimateSliderBrush.ImageSize;

	
	

	MInterface = Cast<UMaterialInterface>(OwningHUD->UISliderBrush.GetResourceObject());
	OwningHUD->PrimaryAbilityMaterialInstance = UMaterialInstanceDynamic::Create(MInterface, OwningHUD->GetWorld()->GetFirstPlayerController());
	PrimaryAbilitySliderBrush.SetResourceObject(OwningHUD->PrimaryAbilityMaterialInstance);
	PrimaryAbilitySliderBrush.ImageSize = OwningHUD->UISliderBrush.ImageSize;
	PrimaryAbilitySliderBrush.TintColor = OwningHUD->UISliderBrush.TintColor;


	

	MInterface = Cast<UMaterialInterface>(OwningHUD->UISliderBrush.GetResourceObject());
	OwningHUD->ElementalAbilityMaterialInstance = UMaterialInstanceDynamic::Create(MInterface, OwningHUD->GetWorld()->GetFirstPlayerController());
	ElementalAbilitySliderBrush.SetResourceObject(OwningHUD->ElementalAbilityMaterialInstance);
	ElementalAbilitySliderBrush.ImageSize = OwningHUD->UISliderBrush.ImageSize;
	ElementalAbilitySliderBrush.TintColor = OwningHUD->UISliderBrush.TintColor;

	
	//---------
	//Weapon


	MInterface = Cast<UMaterialInterface>(OwningHUD->ShargeWeaponSlider.GetResourceObject());
	OwningHUD->ChargeSliderMaterialInstance = UMaterialInstanceDynamic::Create(MInterface, OwningHUD->GetWorld()->GetFirstPlayerController());
	ChargeSliderBrush.SetResourceObject(OwningHUD->ChargeSliderMaterialInstance);
	ChargeSliderBrush.ImageSize = OwningHUD->ShargeWeaponSlider.ImageSize;
	

	
}



#undef LOCTEXT_NAMESPACE