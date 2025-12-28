#include "SP_PlayerHud.h"
#include "SP_HUD.h"

#include "UObject/ConstructorHelpers.h"


#define LOCTEXT_NAMESPACE "PlayerHud"

void SPlayerHud::Construct(const FArguments& InArgs) 
{


	OwningHUD = InArgs._OwningHUD;


	
	HPBrush = OwningHUD->HPImageBrush;

	HealthBarMaterial = Cast<UMaterialInterface>(HPBrush.GetResourceObject());

	MaterialInstance = UMaterialInstanceDynamic::Create(HealthBarMaterial, OwningHUD->GetWorld()->GetFirstPlayerController());

	HPBrush.SetResourceObject(MaterialInstance);

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
		];

}



void SPlayerHud::UpdateAmmoText(int current, int Extra)
{
	CurrntAmmoText = FText::FromString(FString::FromInt(current));
	ExtraAmmoText = FText::FromString(FString::FromInt(Extra));
}

void SPlayerHud::UpdateHPPercent(float percent)
{
	MaterialInstance->SetScalarParameterValue("Percentage", percent);
}



#undef LOCTEXT_NAMESPACE