// Fill out your copyright notice in the Description page of Project Settings.

#include "BlooPaperCharacter.h"
#include <PaperFlipbookComponent.h>

ABlooPaperCharacter::ABlooPaperCharacter() {
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> idleFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_idle_Flipbook.Bloo_idle_Flipbook"));
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> movingFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_moving.Bloo_moving"));
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> jumpingFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_jumping_Flipbook.Bloo_jumping_Flipbook"));
	this->idleFlipbook = idleFlipbookObject.Object;
	this->movingFlipbook = movingFlipbookObject.Object;
	this->jumpingFlipbook = jumpingFlipbookObject.Object;
}

bool isOnTheAir(ABlooPaperCharacter* character) {
	FVector velocity = character->GetVelocity();
	float zVelocity = velocity.Z;
	return zVelocity != 0;
}

void ABlooPaperCharacter::HandleMovement(float scaleValue) {
	FVector vector = FVector::ZeroVector;
	vector.Y = 1;
	AddMovementInput(vector, scaleValue);
	UPaperFlipbookComponent* sprite = GetSprite();
	if (isOnTheAir(this)) {
		sprite->SetFlipbook(this->jumpingFlipbook);
	}
	else {
		if (scaleValue == 0) {
			sprite->SetFlipbook(this->idleFlipbook);
		}
		else if (scaleValue > 0) {
			GetWorld();
			sprite->SetFlipbook(this->movingFlipbook);
			FRotator rotator = FRotator::ZeroRotator;
			sprite->SetRelativeRotation(rotator);
		}
		else if (scaleValue < 0) {
			sprite->SetFlipbook(this->movingFlipbook);
			FRotator rotator = FRotator::ZeroRotator;
			rotator.Yaw = 180;
			sprite->SetRelativeRotation(rotator);
		}
	}
}

void ABlooPaperCharacter::HandleJump() {
	Jump();
}

void ABlooPaperCharacter::HandleStopJump() {
	StopJumping();
}