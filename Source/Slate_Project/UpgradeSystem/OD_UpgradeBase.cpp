#include "OD_UpgradeBase.h"

int UUpgradeBase::CalculateCost()
{
	
	return upgradeResorce.BaseCost + upgradeResorce.BaseCost * UpgradeLevel;
}

void UUpgradeBase::ApplyUpgrade(ASPCharacter*& player)
{
	
}
