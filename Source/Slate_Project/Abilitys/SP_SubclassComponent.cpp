#include "SP_SubclassComponent.h"
#include "SP_Subclass.h"
#include "../SP_Player.h"
#include"CreatedAbilitys/SP_StormWalker.h"
#include"CreatedAbilitys/SP_Pupeter.h"

void USubclassComponent::InitializeSubclasses(ASPCharacter* Holder)
{
	Owner = Holder;
	StormsEya = Cast<AStormWalker>(GetWorld()->SpawnActor<ASubclass>(StormsEya_Template));
	StormsEya->InitializeSubclass(Owner);

	pupeter = Cast<APupeter>(GetWorld()->SpawnActor<ASubclass>(pupeterTemplate));
	pupeter->InitializeSubclass(Owner);
	activeSubclass = pupeter;
	SelectSubclass(Subclasses::Pupeter);
}

void USubclassComponent::SelectSubclass(Subclasses subclass)
{
	switch (subclass)
	{
	case StormWalker:
		StormsEya->SubclassSelected();
		break;
	case Pupeter:
		pupeter->SubclassSelected();
		break;
	default:
		break;
	}
}


