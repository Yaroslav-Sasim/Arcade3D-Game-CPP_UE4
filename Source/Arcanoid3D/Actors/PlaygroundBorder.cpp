// Fill out your copyright notice in the Description page of Project Settings.

#include "PlaygroundBorder.h"
#include "Components/BoxComponent.h"
#include "Pawns/PlayerPawn.h"

// Sets default values
APlaygroundBorder::APlaygroundBorder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Trigger->SetCollisionProfileName("OverlapAll");

}

void APlaygroundBorder::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (!OtherActor) {
		return;
	}

	if (Cast<APlayerPawn>(OtherActor))
	{
		return;
	}

	//UE_LOG(LogTemp, Log, TEXT("Out of playground: %s"), *OtherActor->GetName());
	OtherActor->Destroy();
}
