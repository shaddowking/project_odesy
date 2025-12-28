#pragma once
#include "Components/ActorComponent.h"
#include "SP_SubclassComponent.generated.h"

class ASPCharacter;
class ASubclass;


UCLASS(meta = (BlueprintSpawnableComponent))
class USubclassComponent : public UActorComponent {
	GENERATED_BODY()

public:

	ASPCharacter* Owner;

	void InitializeSubclasses(ASPCharacter* Holder);

	// Subclasses
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASubclass> StormsEya_Template;
	UPROPERTY(BlueprintReadOnly)
	ASubclass* StormsEya = nullptr;

};