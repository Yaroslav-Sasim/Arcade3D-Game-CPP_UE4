// Fill out your copyright notice in the Description page of Project Settings.

#include "ShoootComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values for this component's properties
UShoootComponent::UShoootComponent():ShootPeriod(1.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShoootComponent::BeginPlay()
{
	Super::BeginPlay();

	StartShooting();
	
}

void UShoootComponent::Shoot()
{
	
	for (FShootInfo ShootInfo : ShootInfos)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();

		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SpawnLocation=GetOwner()->GetActorLocation()+ GetOwner()->GetActorRotation().RotateVector(ShootInfo.Offset);
		FRotator SpawnPotator = GetOwner()->GetActorRotation();
		SpawnPotator.Add(0.f, ShootInfo.Angle, 0.f);
	
		AShootProjectile* Projectile= GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnPotator, SpawnParameters);

		if (Projectile)
		{
			Projectile->Damage = ShootInfo.Damage;
		}

		//Projectile->Damage = ShootInfo.Damage;
	}

}

void UShoootComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShoootComponent::Shoot, ShootPeriod, true, ShootPeriod);
}

void UShoootComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}
