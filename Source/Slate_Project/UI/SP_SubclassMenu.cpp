#include "SP_SubclassMenu.h"
#include "../SP_Player.h"
#include "../Abilitys/SP_SubclassComponent.h"

void SSubclassMenu::Construct(const FArguments& InArgs)
{

	FSlateFontInfo SubclassFornt = FCoreStyle::Get().GetFontStyle("EmbossedText");
	SubclassFornt.Size = 10.f;

	const FMargin Buttonpad = FMargin(10.f);

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
						.Font(SubclassFornt)
					]
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			.Padding(FMargin(500.f,300.f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().Padding(Buttonpad)
					[
						SNew(SButton).OnClicked(this, &SSubclassMenu::SelectStormWalker)
						[
							SNew(SImage).ColorAndOpacity(FColor::Blue)

						]
					]
				+ SVerticalBox::Slot().Padding(Buttonpad)
				[
					SNew(SButton).OnClicked(this, &SSubclassMenu::SelectPupeter)
						[
							SNew(SImage).ColorAndOpacity(FColor::Yellow)

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
