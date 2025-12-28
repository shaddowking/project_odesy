#include "SP_GameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/SP_HUD.h"

ASP_GameMode::ASP_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Slate_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//HUDClass = ASP_HUD::StaticClass();
}
