// Fill out your copyright notice in the Description page of Project Settings.

#include "BlooPaperCharacter.h"
#include "Gun.h"
#include <PaperFlipbookComponent.h>

ABlooPaperCharacter::ABlooPaperCharacter() {
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> idleFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_idle_Flipbook.Bloo_idle_Flipbook"));
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> movingFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_moving.Bloo_moving"));
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> jumpingFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_jumping_Flipbook.Bloo_jumping_Flipbook"));
	this->idleFlipbook = idleFlipbookObject.Object;
	this->movingFlipbook = movingFlipbookObject.Object;
	this->jumpingFlipbook = jumpingFlipbookObject.Object;
	this->attachedGun = NULL;
}

bool isOnTheAir(ABlooPaperCharacter* character) {
	FVector velocity = character->GetVelocity();
	float zVelocity = velocity.Z;
	return zVelocity != 0;
}

FRotator GetRightRotator() {
	FRotator rotator = FRotator::ZeroRotator;
	return rotator;
}

FRotator GetLeftRotator() {
	FRotator rotator = FRotator::ZeroRotator;
	rotator.Yaw = 180;
	return rotator;
}

void ABlooPaperCharacter::MoveGun() {
	if (this->attachedGun != NULL) {
		FVector currentPawnLocation = this->GetActorLocation();
		this->attachedGun->SetActorLocation(currentPawnLocation);
		switch (this->facingDirection) {
			case RIGHT:
				this->attachedGun->FaceRight();
				break;
			case LEFT:
				this->attachedGun->FaceLeft();
				break;
		}
	}
}

void ABlooPaperCharacter::HandleMovement(float scaleValue) {
	FVector vector = FVector::ZeroVector;
	vector.Y = 1;
	AddMovementInput(vector, scaleValue);
	MoveGun();
	UPaperFlipbookComponent* sprite = GetSprite();
	if (isOnTheAir(this)) {
		sprite->SetFlipbook(this->jumpingFlipbook);
	}
	else {
		if (scaleValue == 0) {
			sprite->SetFlipbook(this->idleFlipbook);
		}
		else if (scaleValue > 0) {
			this->
			GetWorld();
			sprite->SetFlipbook(this->movingFlipbook);
			sprite->SetRelativeRotation(GetRightRotator());
			this->facingDirection = FACING_DIRECTION::RIGHT;
		}
		else if (scaleValue < 0) {
			sprite->SetFlipbook(this->movingFlipbook);
			sprite->SetRelativeRotation(GetLeftRotator());
			this->facingDirection = FACING_DIRECTION::LEFT;
		}
	}
}

void ABlooPaperCharacter::HandleJump() {
	Jump();
}

void ABlooPaperCharacter::HandleStopJump() {
	StopJumping();
}

void ABlooPaperCharacter::AttachGun(AGun* gun)
{
	if (this->attachedGun == NULL) {
		this->attachedGun = gun;
		this->attachedGun->SetAttached();
	}
}
