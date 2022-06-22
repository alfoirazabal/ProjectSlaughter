// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ConceptDemoPaperPawn.h"

#include "Guns/Gun.h"
#include "Kismet/GameplayStatics.h"

constexpr float GDefault_Character_Plane_X_Position = 760;

// Sets default values
AConceptDemoPaperPawn::AConceptDemoPaperPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void AConceptDemoPaperPawn::EnsureXAxisLocation()
{
	// Prevents actor from moving along the X axis, and move only along the Y and Z axis of the simulated 3D plane.
	FVector CurrentPosition = this->GetActorLocation();
	if (!this->bFallingDeath && CurrentPosition.X != GDefault_Character_Plane_X_Position) {
		CurrentPosition.X = GDefault_Character_Plane_X_Position;
		this->SetActorLocation(CurrentPosition);
	}
}

bool AConceptDemoPaperPawn::IsOnTheAir() const
{
	const FVector Velocity = this->GetVelocity();
	const float ZVelocity = Velocity.Z;
	return ZVelocity != 0;
}

FRotator AConceptDemoPaperPawn::GetRightRotator()
{
	const FRotator Rotator = FRotator::ZeroRotator;
	return Rotator;
}

FRotator AConceptDemoPaperPawn::GetLeftRotator()
{
	FRotator Rotator = FRotator::ZeroRotator;
	Rotator.Yaw = 180;
	return Rotator;
}

FRotator AConceptDemoPaperPawn::GetFacingRotation() const
{
	FRotator Rotator = FRotator::ZeroRotator;
	switch (this->FacingDirection)
	{
	case Left:
		Rotator = FRotator(0, -90, 0);
		break;
	case Right:
		Rotator = FRotator(0, 90, 0);
		break;
	default:
		break;
	}
	return Rotator;
}

// Called when the game starts or when spawned
void AConceptDemoPaperPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConceptDemoPaperPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConceptDemoPaperPawn::SetPlayerNumber(const TEnumAsByte<EAutoReceiveInput::Type> PlayerNumber)
{
	AutoReceiveInput = PlayerNumber;
}

// Called to bind functionality to input
void AConceptDemoPaperPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

