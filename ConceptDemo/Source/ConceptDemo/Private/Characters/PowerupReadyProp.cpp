// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PowerupReadyProp.h"

// Sets default values
APowerupReadyProp::APowerupReadyProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->DisplayTime = 1;
	this->SpawnActorRelativeLocation = FVector(50, 0, 0);
}

void APowerupReadyProp::Disappear()
{
	this->Destroy();
}

// Called when the game starts or when spawned
void APowerupReadyProp::BeginPlay()
{
	Super::BeginPlay();

	if (!this->ActorToFollow)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2, FColor::Red, "PROGRAMMING ERROR: PowerUp Ready prop has no Actor to Follow. Will not follow actor");
	}
	
	FTimerHandle TimerHandle;
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APowerupReadyProp::Disappear, this->DisplayTime, false);
}

// Called every frame
void APowerupReadyProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->ActorToFollow)
	{
		FVector NewLocation = this->ActorToFollow->GetActorLocation();
		NewLocation += this->SpawnActorRelativeLocation;
		this->SetActorLocation(NewLocation);
	}
}

