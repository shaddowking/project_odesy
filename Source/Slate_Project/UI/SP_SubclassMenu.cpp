#include "SP_SubclassMenu.h"
#include "../SP_Player.h"
#include "../Abilitys/SP_SubclassComponent.h"

void SSubclassMenu::Construct(const FArguments& InArgs)
{

	FSlateFontInfo SubclassFornt = FCoreStyle::Get().GetFontStyle("EmbossedText");
	SubclassFornt.Size = 50.f;
	FSlateFontInfo ExitFornt = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ExitFornt.Size = 15.f;


	OwningHUD = InArgs._OwningHUD;
	OwningCharacter = InArgs._OwningCharacter;

	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage).ColorAndOpacity(FColor::Purple)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(40.f, 40.f))
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			[
				SNew(SButton).OnClicked(this, &SSubclassMenu::HideMenu)
					[
						SNew(STextBlock)
							
						.Text(FText::FromString(TEXT("HideSubclassMeny")))
						.Justification(ETextJustify::Center)
						.Font(ExitFornt)
					]
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.Padding(FMargin(100.f,0))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().Padding(FMargin(100.f, 100.f))
					[
						SNew(SButton).ButtonColorAndOpacity(FColor::Blue).OnClicked(this, &SSubclassMenu::SelectStormWalker)
						[
							SNew(STextBlock)

								.Text(FText::FromString(TEXT("StormWalker")))
								.Justification(ETextJustify::Center)
								.Font(SubclassFornt)
						]
					]
				+ SVerticalBox::Slot().Padding(FMargin(100.f, 100.f))
				[
					SNew(SButton).ButtonColorAndOpacity(FColor::Yellow).OnClicked(this, &SSubclassMenu::SelectPupeter)
						[
							SNew(STextBlock)

								.Text(FText::FromString(TEXT("Pupeter")))
								.Justification(ETextJustify::Center)
								.Font(SubclassFornt)

						]
				]
			]
		];

}

FReply SSubclassMenu::SelectStormWalker() const
{
	OwningCharacter->SCcomponent->SelectSubclass(ESubclasses::StormWalker);
	OwningHUD->HideSubclassMenu();

	return FReply::Handled();
}

FReply SSubclassMenu::SelectPupeter() const
{
	OwningCharacter->SCcomponent->SelectSubclass(ESubclasses::Pupeter);
	OwningHUD->HideSubclassMenu();

	return FReply::Handled();
}

FReply SSubclassMenu::HideMenu() const
{
	OwningHUD->HideSubclassMenu();
	return FReply::Handled();
}
