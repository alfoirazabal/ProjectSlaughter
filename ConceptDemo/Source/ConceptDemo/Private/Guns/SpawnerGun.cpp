// Fill out your copyright notice in the Description page of Project Settings.


#include "Guns/SpawnerGun.h"

// Sets default values
ASpawnerGun::ASpawnerGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawnerGun::BeginPlay()
{
	Super::BeginPlay();
	
}

