// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Pawns/PlayerPawn.h"
#include "Actors/Other/PawnShield.h"

void ABonusShield::BonusColleted_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) {
		return;
	}
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);
	
	if (!PlayerPawn)
	{
		return;
	}

	if (!PlayerPawn)
	{
		return;
	}
	
	APawnShield* Shield= GetWorld()->SpawnActor<APawnShield>(ShieldClass);
	Shield->ActivateShield(PlayerPawn);

	Super::BonusColleted_Implementation();
}


