// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "Arcanoid3DGameModeBase.h"

void ABonusPoints::BonusColleted_Implementation()
{
	AArcanoid3DGameModeBase* GameMode = Cast<AArcanoid3DGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->AddPoints(Points);
	}
	Destroy();

	Super::BonusColleted_Implementation();
}
