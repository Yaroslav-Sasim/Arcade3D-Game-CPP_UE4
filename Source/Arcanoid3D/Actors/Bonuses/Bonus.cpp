// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"

// Sets default values
ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	RootComponent = Collision;
	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	/*Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);*/

	Collision->SetSphereRadius(100);
}


void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (!OtherActor) {
		return;
	}
	if (!Cast<APlayerPawn>(OtherActor)) {
		return;
	}
	BonusColleted();
}

void ABonus::BonusColleted_Implementation()
{
	if (CollectedParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectedParticle, GetActorTransform(), true);
	Destroy();
}
// Called every frame
void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorlMoveOffset = -200.f * DeltaTime;
	AddActorWorldOffset(FVector(WorlMoveOffset, 0.f, 0.f));
}


