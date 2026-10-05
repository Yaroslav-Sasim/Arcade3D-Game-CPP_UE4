 // Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Materials/MaterialInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerPawn::APlayerPawn():TouchMoveSensetivity(1.f), MoveLimit(FVector2D (500.f,600.f))
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent=PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");
	PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);

	/*CamSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamSpringArm"));
	CamSpringArm->SetupAttachment(RootComponent);*/

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	//PawnCamera->SetupAttachment(CamSpringArm);
	ShootComponent = CreateDefaultSubobject<UShoootComponent>(TEXT("ShootComponent"));

}

void APlayerPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

bool APlayerPawn::CanBeDamage_Implementation()
{
	return bCanBeDamaged;
}



void APlayerPawn::ExplodePawn_Implementation()
{
	SetActorEnableCollision(false);

	

	ShootComponent->StopShooting();

	PawnMesh->SetMaterial(0,RecoverMaterial);
	if(DestroyParticle)
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass())) {
		Component->Deactivate();
	}
}

void APlayerPawn::RecoverPawn_Implementation()
{
	SetActorEnableCollision(true);
	ShootComponent->StartShooting();

	PawnMesh->SetMaterial(0, PawnMaterial);
	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass())) {
		Component->Activate(true);
	}
}





// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PawnMaterial=PawnMesh->GetMaterial(0);
	
}

float APlayerPawn::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!CanBeDamage())
	{
		return 0.f;
	}
	Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser);
	PawnDamaged.Broadcast();
	return Damage;
}


// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);
	//InputComponent->BindTouch(IE_Released, this, &APlayerPawn::OnTouchRelease);

	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);

}

//Touch controlls

void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	



	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);
	//UE_LOG(LogTemp, Log, TEXT("Touching in %f-%f"), TouchLocation.X - TouchX, TouchLocation.Y - TouchY);

	TouchDeltaMove = TouchDeltaMove * TouchMoveSensetivity;

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -600.f, 300.f);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, -580.f, 580.f);

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	//UE_LOG(LogTemp, Log, TEXT("Released : %s"), *TouchLocation.ToString());
	TouchLocation = FVector2D(Location.X, Location.Y);
}

