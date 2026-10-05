// Fill out your copyright notice in the Description page of Project Settings.

#include "Arcanoid3DGameModeBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"

AArcanoid3DGameModeBase::AArcanoid3DGameModeBase():PlayerRecoverTime(3),CurrentShootLevel(-1)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcanoid3DGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AArcanoid3DGameModeBase::EndGame);

	PlayerPawn=Cast<APlayerPawn>( UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) {
		return;
	}

	ChangeShootLevel(true);

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[0].ShootInfos;
	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcanoid3DGameModeBase::ExplodePawn);

	
}

void AArcanoid3DGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();
	HealthsComponent->ChangeHealths(-1);
	ChangeShootLevel(false);
	if (!IsGameOver)
	{
      GetWorld()->GetTimerManager().SetTimer(RecoverTime, this, &AArcanoid3DGameModeBase::RecoverPawn_Implementation, PlayerRecoverTime, false);
	}
	
}

void AArcanoid3DGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}



void AArcanoid3DGameModeBase::EndGame()
{
	IsGameOver = true;
	EnemySpawnController->SetActive(false);
	GameOver.Broadcast();
	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	SetPause(UGameplayStatics::GetPlayerController(this, 0), false);
}

void AArcanoid3DGameModeBase::AddPoints(int points)
{
	GamePoints +=points;
}

bool AArcanoid3DGameModeBase::ChangeShootLevel(bool Up)
{
	UE_LOG(LogTemp, Log, TEXT("Activate PR"));
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this,0));
	if (!PlayerPawn)
	{
		return false;
	}
	UE_LOG(LogTemp, Log, TEXT("Activate PR 2"));
	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1),0, ShootInfoLevels.Num()-1);
	UE_LOG(LogTemp, Log, TEXT("Activate PR 5"));
	/*if (NewLevel == CurrentShootLevel) {
		return false;
	}*/
	UE_LOG(LogTemp, Log, TEXT("Activate PR 3"));
	CurrentShootLevel = NewLevel;
	UE_LOG(LogTemp, Log, TEXT("Activate PR 4"));
	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;
	return true;
}


