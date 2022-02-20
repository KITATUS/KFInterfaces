// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KFI_Interact.generated.h"

UINTERFACE(MinimalAPI)
class UKFI_Interact : public UInterface
{
	GENERATED_BODY()
};

class KFINTERFACES_API IKFI_Interact
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact|FromInteract")
	void EnteredInteractionZone(AActor* InteractableActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact|FromInteract")
	void LeftInteractionZone(AActor* InteractableActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact|ToInteract")
	void InteractRequest(AActor* InteractableActor);
};
