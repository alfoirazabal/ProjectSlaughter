// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/SpikesObject.h"

// Sets default values
ASpikesObject::ASpikesObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpikesObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikesObject::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

