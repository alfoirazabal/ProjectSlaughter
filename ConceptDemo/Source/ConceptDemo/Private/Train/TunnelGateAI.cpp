// Fill out your copyright notice in the Description page of Project Settings.


#include "Train/TunnelGateAI.h"

// Sets default values
ATunnelGateAI::ATunnelGateAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATunnelGateAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATunnelGateAI::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

