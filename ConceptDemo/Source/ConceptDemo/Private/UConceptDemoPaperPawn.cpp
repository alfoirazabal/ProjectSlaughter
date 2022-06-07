// Fill out your copyright notice in the Description page of Project Settings.


#include "UConceptDemoPaperPawn.h"

// Sets default values
AUConceptDemoPaperPawn::AUConceptDemoPaperPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUConceptDemoPaperPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUConceptDemoPaperPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUConceptDemoPaperPawn::SetPlayerNumber(const TEnumAsByte<EAutoReceiveInput::Type> PlayerNumber)
{
	AutoReceiveInput = PlayerNumber;
}

// Called to bind functionality to input
void AUConceptDemoPaperPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

