#pragma once
#include "Components/ActorComponent.h"
#include "SP_SubclassComponent.generated.h"

class ASPCharacter;
class ASubclass;
class AStormWalker;
class APupeter;


UENUM(BlueprintType)
enum Subclasses
{
StormWalker,
Pupeter
};

UCLASS(meta = (BlueprintSpawnableComponent))
class USubclassComponent : public UActorComponent {
	GENERATED_BODY()

public:

	ASPCharacter* Owner;

	void InitializeSubclasses(ASPCharacter* Holder);
	void SelectSubclass(Subclasses subclass);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ASubclass* activeSubclass = nullptr;

	// Subclasses
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASubclass> StormsEya_Template;
	UPROPERTY(BlueprintReadOnly)
	AStormWalker* StormsEya = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASubclass> pupeterTemplate;

	UPROPERTY(BlueprintReadOnly)
	APupeter* pupeter = nullptr;


};