// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGameHealthComponent::UGameHealthComponent():Healths(3)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(this,0);
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp,Error, TEXT("No playerPawn!!!"));
		return;
	}
//	PlayerPawn->OnTakeAnyDamage.AddDynamic(this, &UGameHealthComponent::OnPlayerDamaged);
}

void UGameHealthComponent::OnPlayerDamaged()
{
	ChangeHealths(-1);
}

void UGameHealthComponent::ChangeHealths(int ByValue)
{
	Healths += ByValue;
	HealthsChanged.Broadcast(ByValue);
	if (Healths <= 0)
	{
		HealthsEnded.Broadcast();
	}
	UE_LOG(LogTemp,Log,TEXT("Health %i"),Healths);
}

int UGameHealthComponent::GetHealths()
{
	return Healths;
}

