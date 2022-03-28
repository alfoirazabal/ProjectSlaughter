// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

const int ROTATION_TIME_DS = 150;

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->rotate = false;
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

