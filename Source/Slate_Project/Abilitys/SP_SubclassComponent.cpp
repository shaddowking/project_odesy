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
	activeSublcassEnum = ESubclasses::NoClass;
	SelectSubclass(StartSublcassEnum);
}

void USubclassComponent::SelectSubclass(ESubclasses subclass)
{
	if (activeSublcassEnum != subclass)
	{
		switch (subclass)
		{
		case ESubclasses::StormWalker:
			if (activeSubclass)
			{
				activeSubclass->DeselectSubclass();
			}
			activeSubclass = StormsEya;
			activeSublcassEnum = subclass;
			StormsEya->SubclassSelected();
			break;
		case ESubclasses::Pupeter:
			if (activeSubclass)
			{
				activeSubclass->DeselectSubclass();
			}
			activeSubclass = pupeter;
			activeSublcassEnum = subclass;
			pupeter->SubclassSelected();
			break;
		default:
			break;
		}
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


