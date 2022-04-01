// Fill out your copyright notice in the Description page of Project Settings.

#include "BlooPaperCharacter.h"
#include "Gun.h"
#include <PaperFlipbookComponent.h>

const float DEFAULT_CHARACTER_PLANE_X_POSITION = 760;

ABlooPaperCharacter::ABlooPaperCharacter() {
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> idleFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_idle_Flipbook.Bloo_idle_Flipbook"));
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> movingFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_moving.Bloo_moving"));
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> jumpingFlipbookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_jumping_Flipbook.Bloo_jumping_Flipbook"));
	this->idleFlipbook = idleFlipbookObject.Object;
	this->movingFlipbook = movingFlipbookObject.Object;
	this->jumpingFlipbook = jumpingFlipbookObject.Object;
	this->attachedGun = NULL;

	this->initialPosition = FVector::ZeroVector;
}

void ABlooPaperCharacter::BeginPlay() {
	Super::BeginPlay();
	this->initialPosition = this->GetActorLocation();
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

void EnsureXAxisLocation(ABlooPaperCharacter* character) {
	// Prevents actor from moving along the X axis, and move only along the Y and Z axis of the simulated 3D plane.
	FVector currentPosition = character->GetActorLocation();
	if (currentPosition.X != DEFAULT_CHARACTER_PLANE_X_POSITION) {
		currentPosition.X = DEFAULT_CHARACTER_PLANE_X_POSITION;
		character->SetActorLocation(currentPosition);
	}
}

void respawn(ABlooPaperCharacter* bloo) {
	bloo->SetActorLocation(bloo->initialPosition);
}

void CheckCharacterFall(ABlooPaperCharacter* bloo) {
	if (bloo->GetActorLocation().Z <= levelsZFallLimit) {
		respawn(bloo);
	}
}

void ABlooPaperCharacter::MoveGun() {
	if (this->attachedGun != NULL) {
		this->attachedGun->facingDirection = this->facingDirection;
		this->attachedGun->SetActorLocation(this->GetActorLocation());
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
	EnsureXAxisLocation(this);
	CheckCharacterFall(this);
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

void ABlooPaperCharacter::Fire() {
	if (this->attachedGun != NULL) {
		this->attachedGun->Fire();
	}
}