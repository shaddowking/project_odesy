#pragma once
#include "Components/ActorComponent.h"
#include "SP_SubclassComponent.generated.h"

class ASPCharacter;
class ASubclass;
class AStormWalker;
class APupeter;
class AAbilityBase;

UENUM(BlueprintType)
enum class ESubclasses : uint8
{
StormWalker,
Pupeter
};

UCLASS(meta = (BlueprintSpawnableComponent))
class USubclassComponent : public UActorComponent {
	GENERATED_BODY()

public:

	ASPCharacter* Owner;

	UPROPERTY(EditAnywhere)
	ESubclasses activeSublcassEnum = ESubclasses::StormWalker;

	void InitializeSubclasses(ASPCharacter* Holder);
	void SelectSubclass(ESubclasses subclass);

	bool IsUsingAbility(AAbilityBase*& ability);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ASubclass* activeSubclass = nullptr;

	// Subclasses
	UPROPERTY(EditAnywhere)
	TSubclassOf<AStormWalker> StormsEya_Template;
	UPROPERTY(BlueprintReadOnly)
	AStormWalker* StormsEya = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APupeter> pupeterTemplate;

	UPROPERTY(BlueprintReadOnly)
	APupeter* pupeter = nullptr;


};