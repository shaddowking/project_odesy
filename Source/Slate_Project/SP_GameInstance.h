#pragma once 

#include "Engine/GameInstance.h"
#include "SP_GameInstance.generated.h"

class ABuildGridManager;
class AExploreManager;
UCLASS()
class USPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	ABuildGridManager* BaseGridManager = nullptr;

	UPROPERTY(BlueprintReadWrite)
	AExploreManager* ExploreManager = nullptr;
};