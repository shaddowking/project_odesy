#include "SP_SubclassComponent.h"
#include "SP_Subclass.h"
#include "../SP_Player.h"
#include"CreatedAbilitys/SP_StormWalker.h"

void USubclassComponent::InitializeSubclasses(ASPCharacter* Holder)
{
	Owner = Holder;
	StormsEya = Cast<AStormWalker>(GetWorld()->SpawnActor<ASubclass>(StormsEya_Template));
	StormsEya->InitializeSubclass(Owner);
}
