// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "KFI_Interact.h"
#include "GameFramework/Actor.h"
#include "KF_Interact_Text.generated.h"

class UTextRenderComponent;
class USphereComponent;

UCLASS()
class KFINTERFACES_API AKF_Interact_Text : public AActor, public IKFI_Interact
{
	GENERATED_BODY()

public:
	AKF_Interact_Text();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
	int iTimesInteractedWith;

	UPROPERTY()
	UTextRenderComponent* Txt_InVolume;

	UPROPERTY()
	UTextRenderComponent* Txt_InteractionNumber;
	
	UPROPERTY()
    UTextRenderComponent* Txt_Line01;
    
    UPROPERTY()
    UTextRenderComponent* Txt_Line03;
    
    UPROPERTY()
    USphereComponent* SphereComp;
    
    UFUNCTION(BlueprintNativeEvent, Category="Overlap")
    void OverlapStarted(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category="Overlap")
	void OverlapEnded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void InteractRequest_Implementation(AActor* InteractableActor) override;
};
