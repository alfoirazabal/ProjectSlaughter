// Fill out your copyright notice in the Description page of Project Settings.

#include "BlooPaperCharacter.h"

constexpr float GDefault_Character_Plane_X_Position = 760;

ABlooPaperCharacter::ABlooPaperCharacter()
{
	const ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleFlipBookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_idle_Flipbook.Bloo_idle_Flipbook"));
	const ConstructorHelpers::FObjectFinder<UPaperFlipbook> MovingFlipBookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_moving.Bloo_moving"));
	const ConstructorHelpers::FObjectFinder<UPaperFlipbook> JumpingFlipBookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_jumping_Flipbook.Bloo_jumping_Flipbook"));
	this->IdleFlipBook = IdleFlipBookObject.Object;
	this->MovingFlipBook = MovingFlipBookObject.Object;
	this->JumpingFlipBook = JumpingFlipBookObject.Object;
}

void ABlooPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABlooPaperCharacter::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}