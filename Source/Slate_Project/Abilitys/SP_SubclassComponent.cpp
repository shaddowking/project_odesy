#include "SP_SubclassComponent.h"
#include "SP_Subclass.h"
#include "../SP_Player.h"

void USubclassComponent::InitializeSubclasses(ASPCharacter* Holder)
{
	Owner = Holder;
	StormsEya = GetWorld()->SpawnActor<ASubclass>(StormsEya_Template);
	StormsEya->InitializeSubclass(Owner);
}
