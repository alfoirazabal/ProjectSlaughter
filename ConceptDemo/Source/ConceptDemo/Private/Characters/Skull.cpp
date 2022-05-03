// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skull.h"

// Sets default values
ASkull::ASkull()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpawnXDistance = -200;
	this->DisappearanceTime = 500;
	this->DisappearanceTimeLeft = this->DisappearanceTime;
}

// Called when the game starts or when spawned
void ASkull::BeginPlay()
{
	Super::BeginPlay();
	FVector Location = this->GetActorLocation();
	Location.X += this->SpawnXDistance;
	this->SetActorLocation(Location);
}

// Called every frame
void ASkull::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->DisappearanceTimeLeft--;
	if (this->DisappearanceTimeLeft == 0)
	{
		this->Destroy();
	}
}

