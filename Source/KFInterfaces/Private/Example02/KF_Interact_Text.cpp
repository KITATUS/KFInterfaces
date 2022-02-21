// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example02/KF_Interact_Text.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"

AKF_Interact_Text::AKF_Interact_Text()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(FName("SceneComp"));
    SphereComp->InitSphereRadius(150.0f);
    SetRootComponent(SphereComp);
    
    Txt_InVolume = CreateDefaultSubobject<UTextRenderComponent>(FName("Txt_InVolume"));
	Txt_InVolume->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Txt_InVolume->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	Txt_InVolume->SetText(FText::FromString("NO"));
    Txt_InVolume->SetupAttachment(SphereComp);
    
    Txt_InteractionNumber = CreateDefaultSubobject<UTextRenderComponent>(FName("Txt_InteractionNumber"));
	Txt_InteractionNumber->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Txt_InteractionNumber->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	Txt_InteractionNumber->SetText(FText::FromString("0 TIMES"));
    Txt_InteractionNumber->SetupAttachment(SphereComp);
    
    Txt_Line01 = CreateDefaultSubobject<UTextRenderComponent>(FName("Txt_Line01"));
	Txt_Line01->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Txt_Line01->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	Txt_Line01->SetText(FText::FromString("PLAYER IS IN VOLUME:"));
    Txt_Line01->SetupAttachment(SphereComp);
    
    Txt_Line03 = CreateDefaultSubobject<UTextRenderComponent>(FName("Txt_Line03"));
	Txt_Line03->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Txt_Line03->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	Txt_Line03->SetText(FText::FromString("PLAYER HAS INTERACTED WITH THIS"));
    Txt_Line03->SetupAttachment(SphereComp);
    
    Txt_InVolume->SetRelativeLocation(FVector(0.0f,0.0f,-20.0f));
    Txt_Line03->SetRelativeLocation(FVector(0.0f,0.0f,-40.0f));
    Txt_InteractionNumber->SetRelativeLocation(FVector(0.0f,0.0f,-60.0f));
}

void AKF_Interact_Text::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AKF_Interact_Text::OverlapStarted);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AKF_Interact_Text::OverlapEnded);
	Txt_InVolume->SetText(FText::FromString("NO"));
	Txt_InVolume->SetTextRenderColor(FColor::Red);
}

void AKF_Interact_Text::InteractRequest_Implementation(AActor* InteractableActor)
{
	IKFI_Interact::InteractRequest_Implementation(InteractableActor);

	iTimesInteractedWith += 1;

	FString TempString = FString::FromInt(iTimesInteractedWith);
	TempString.Append(" TIMES");
	Txt_InteractionNumber->SetText(FText::FromString(*TempString));
}

void AKF_Interact_Text::OverlapStarted_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if(OtherActor->Implements<UKFI_Interact>())
	{
		IKFI_Interact::Execute_EnteredInteractionZone(OtherActor, this);
		Txt_InVolume->SetText(FText::FromString("YES"));
		Txt_InVolume->SetTextRenderColor(FColor::Green);
	}
}

void AKF_Interact_Text::OverlapEnded_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	if(OtherActor->Implements<UKFI_Interact>())
	{
		IKFI_Interact::Execute_LeftInteractionZone(OtherActor, this);
		Txt_InVolume->SetText(FText::FromString("NO"));
		Txt_InVolume->SetTextRenderColor(FColor::Red);
	}
}