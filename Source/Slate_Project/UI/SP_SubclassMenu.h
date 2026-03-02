#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "../SP_Player.h"
#include "SP_HUD.h"

class SSubclassMenu : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SSubclassMenu) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ASP_HUD>, OwningHUD)

	SLATE_ARGUMENT(TWeakObjectPtr<class ASPCharacter>, OwningCharacter)


	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class ASP_HUD> OwningHUD;

	TWeakObjectPtr<class ASPCharacter> OwningCharacter;


	FReply SelectStormWalker() const;

	FReply SelectPupeter() const;

	FReply HideMenu() const;


	virtual bool SupportsKeyboardFocus() const override { return true; }

};

