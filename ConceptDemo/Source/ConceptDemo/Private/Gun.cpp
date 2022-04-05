// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

const int ROTATION_TIME_DS = 150;

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->rotate = true;
	this->rotationSpeed = 1;

	this->bulletSpawnRelativeLocation = FVector(0.0f, 50.0f, 10.0f);

	this->bulletClass = NULL;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	this->initialLocation = this->GetActorLocation();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (rotate) {
		int rotationTime = (DeltaTime * ROTATION_TIME_DS) * rotationSpeed;
		FRotator rotator = FRotator::ZeroRotator;
		rotator.Yaw = rotationTime;
		AddActorLocalRotation(rotator);
	}
	else {
		FRotator rotator = FRotator::ZeroRotator;
		switch (this->facingDirection) {
			case FACING_DIRECTION::LEFT:
				rotator.Yaw = 270;
				break;
			case FACING_DIRECTION::RIGHT:
				rotator.Yaw = 90;
				break;
		}
		this->SetActorRotation(rotator);
	}
}

void AGun::SetAttached() {
	this->rotate = false;
	this->SetActorEnableCollision(false);
	this->SetActorScale3D(FVector(0.7f, 0.7f, 0.7f));
}

void AGun::SetDetached() {
	this->rotate = true;
	this->SetActorEnableCollision(true);
	this->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void AGun::Fire() {
	if (this->bulletClass != NULL) {
		FVector bulletLocation = this->GetActorLocation();
		bulletLocation.Z += this->bulletSpawnRelativeLocation.Z;
		if (this->facingDirection == FACING_DIRECTION::LEFT) {
			bulletLocation.Y -= this->bulletSpawnRelativeLocation.Y;
		}
		else if (this->facingDirection == FACING_DIRECTION::RIGHT) {
			bulletLocation.Y += this->bulletSpawnRelativeLocation.Y;
		}
		ABullet* bullet = this->GetWorld()->SpawnActor<ABullet>(this->bulletClass, bulletLocation, this->GetActorRotation());
		bullet->FacingDirection = this->facingDirection;
		bullet->TravelSpeed = 15;
		bullet->MaxTravelDistance = 5000;
		bullet->fireSource = this;
	}
	else {
		GEngine->AddOnScreenDebugMessage(23425, 10, FColor::Red, "ERR: Bullet class unset for gun: " + this->GetName());
	}
}

void AGun::Respawn() {
	this->SetActorLocation(this->initialLocation);
}