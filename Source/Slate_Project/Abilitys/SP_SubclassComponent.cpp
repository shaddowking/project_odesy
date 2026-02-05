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
	
	SelectSubclass(activeSublcassEnum);
}

void USubclassComponent::SelectSubclass(ESubclasses subclass)
{
	switch (subclass)
	{
	case ESubclasses::StormWalker:
		activeSubclass = StormsEya;
		StormsEya->SubclassSelected();
		break;
	case ESubclasses::Pupeter:
		activeSubclass = pupeter;
		pupeter->SubclassSelected();
		break;
	default:
		break;
	}
}

bool USubclassComponent::IsUsingAbility(AAbilityBase*& ability)
{
	if (activeSubclass->ActiveAbility == nullptr)
	{
		return false;
	}

	return ability == activeSubclass->ActiveAbility;
}


