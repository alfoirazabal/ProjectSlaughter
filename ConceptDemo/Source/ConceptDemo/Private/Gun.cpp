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
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
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
}

void AGun::FaceRight() {
	FRotator rotator = FRotator::ZeroRotator;
	rotator.Yaw = 90;
	rotator.Pitch = 0;
	rotator.Roll = 0;
	this->SetActorRotation(rotator);
}

void AGun::FaceLeft() {
	FRotator rotator = FRotator::ZeroRotator;
	rotator.Yaw = 270;
	rotator.Pitch = 0;
	rotator.Roll = 0;
	this->SetActorRotation(rotator);
}

void AGun::SetAttached() {
	this->rotate = false;
	this->SetActorEnableCollision(false);
	this->SetActorScale3D(FVector(0.7f, 0.7f, 0.7f));
}

