// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Death/DeathIndicator.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADeathIndicator::ADeathIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->PlayerMoveXDistance = -6;
	this->PlayerMoveYDistance = 0;
	this->SpawnXDistance = -190;
	this->SpawnYDistance = 0;
	this->DisplayTime = 1.5;
	this->PlayerMoveXOnDestroyDistance = -500;
	this->PlayerMoveYOnDestroyDistance = 0;
}

void ADeathIndicator::Disappear()
{
	if (this->DeadCharacter)
	{
		FVector CurrentCharacterLocation = this->DeadCharacter->GetActorLocation();
		CurrentCharacterLocation.X += this->PlayerMoveXOnDestroyDistance;
		CurrentCharacterLocation.Y += this->PlayerMoveYOnDestroyDistance;
		this->DeadCharacter->SetActorLocation(CurrentCharacterLocation);
		this->PlayerController->SetIgnoreMoveInput(false);
		this->DeadCharacter->Frozen = false;
	}
	this->Destroy();
}

// Called when the game starts or when spawned
void ADeathIndicator::BeginPlay()
{
	Super::BeginPlay();

	FVector CurrentLocation = this->GetActorLocation();
	CurrentLocation.X += this->SpawnXDistance;
	CurrentLocation.Y += this->SpawnYDistance;
	this->SetActorLocation(CurrentLocation);
	
	if (this->DeadCharacter)
	{
		FVector CurrentCharacterPosition = this->GetActorLocation();
		CurrentCharacterPosition.X += this->PlayerMoveXDistance;
		CurrentCharacterPosition.Y += this->PlayerMoveYDistance;
		this->DeadCharacter->SetActorLocation(CurrentCharacterPosition);
		this->PlayerController = this->DeadCharacter->GetController();
		this->PlayerController->SetIgnoreMoveInput(true);
		this->DeadCharacter->Frozen = true;
	}
	
	FTimerHandle TimerHandle;
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADeathIndicator::Disappear, this->DisplayTime, false);
}

// Called every frame
void ADeathIndicator::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

