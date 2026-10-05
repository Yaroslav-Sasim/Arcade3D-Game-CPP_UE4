// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShootLevelUp.h"
#include "Kismet/GameplayStatics.h"
#include "Arcanoid3DGameModeBase.h"

void ABonusShootLevelUp::BonusColleted_Implementation()
{
	AArcanoid3DGameModeBase* GameMode = Cast<AArcanoid3DGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode)
	{
		return;
	}
	GameMode->ChangeShootLevel(true);

	Super::BonusColleted_Implementation();
}



