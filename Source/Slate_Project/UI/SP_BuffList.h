#pragma once 

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "SP_BuffList.generated.h"


class UBuffUI;

UCLASS()
class UBuffList : public UUserWidget
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void AddBuffUIToList(UBuffUI* buff);

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveBuffUIfromList(UBuffUI* buff);

};