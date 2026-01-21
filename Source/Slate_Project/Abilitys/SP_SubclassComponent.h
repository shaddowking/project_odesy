#pragma once
#include "Components/ActorComponent.h"
#include "SP_SubclassComponent.generated.h"

class ASPCharacter;
class ASubclass;
class AStormWalker;


UCLASS(meta = (BlueprintSpawnableComponent))
class USubclassComponent : public UActorComponent {
	GENERATED_BODY()

public:

	ASPCharacter* Owner;

	void InitializeSubclasses(ASPCharacter* Holder);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ASubclass* activeSubclass = nullptr;

	// Subclasses
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASubclass> StormsEya_Template;
	UPROPERTY(BlueprintReadOnly)
	AStormWalker* StormsEya = nullptr;


};