// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ConceptDemoPaperPawn.h"

// Sets default values
AConceptDemoPaperPawn::AConceptDemoPaperPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

