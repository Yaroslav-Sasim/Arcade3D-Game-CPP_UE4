// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/Projectiles/ShootProjectile.h"
#include "ShoootComponent.generated.h"

USTRUCT(BlueprintType)
struct  FShootInfo
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float Damage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float Angle;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCANOID3D_API UShoootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShoootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Shoot();

	FTimerHandle ShootingTimer;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StopShooting();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	float ShootPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	TArray<	FShootInfo> ShootInfos;
	
};
