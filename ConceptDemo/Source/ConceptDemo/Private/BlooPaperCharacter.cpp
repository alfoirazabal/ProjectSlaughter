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

	this->lives = 3;
	this->lifeSize = 1;

	this->currentLives = this->lives;
	this->currentLifeSize = this->lifeSize;

	this->initialPosition = FVector::ZeroVector;

	this->blooHealthHUD = NULL;
}

void ABlooPaperCharacter::BeginPlay() {
	Super::BeginPlay();
	this->initialPosition = this->GetActorLocation();
	TArray<UActorComponent*> components;
	this->GetComponents(components);
	UWidgetComponent* healthHUDWidgetComponent = nullptr;
	for (int i = 0; healthHUDWidgetComponent == nullptr && i < components.Num(); i++) {
		healthHUDWidgetComponent = Cast<UWidgetComponent>(components[i]);
	}
	if (healthHUDWidgetComponent) {
		GEngine->AddOnScreenDebugMessage(564564, 2, FColor::Cyan, healthHUDWidgetComponent->GetName());
		UUserWidget* healthHUDWidget = healthHUDWidgetComponent->GetWidget();
		this->blooHealthHUD = Cast<UBlooHealthHUD>(healthHUDWidget);
		if (!this->blooHealthHUD) {
			GEngine->AddOnScreenDebugMessage(5345343, 2, FColor::Red, "Unable to cast HealthHUD to BlooHealthHUD for BlooPaperCharacter!");
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(564564, 2, FColor::Red, "HealthHUD not found!");
	}
}

void ABlooPaperCharacter::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	TArray<AActor*> overlappingActors;
	this->GetOverlappingActors(overlappingActors);
	for (int i = 0; i < overlappingActors.Num(); i++) {
		ABullet* bullet = Cast<ABullet>(overlappingActors[i]);
		if (bullet) {
			if (
				(this->attachedGun != NULL && bullet->fireSource != this->attachedGun) ||
				this->attachedGun == NULL
			) {
				bullet->Destroy();
				this->TakeDamage(0.1f);
			}
		}
	}
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

void ABlooPaperCharacter::UpdateHealthIndicator() 
{
	if (this->blooHealthHUD) {
		this->blooHealthHUD->SetHealth(this->currentLifeSize);
		this->blooHealthHUD->SetLives(this->currentLives);
	}
}

void ABlooPaperCharacter::Respawn() {
	if (this->attachedGun != NULL) {
		AGun* gun = this->attachedGun;
		this->DropGun();
		gun->Respawn();
	}
	this->SetActorLocation(this->initialPosition);
}

void ABlooPaperCharacter::CheckCharacterFall() {
	if (this->GetActorLocation().Z <= levelsZFallLimit) {
		this->currentLives--;
		this->currentLifeSize = this->lifeSize;
		if (this->currentLives == 0) {
			this->Die();
		}
		else {
			this->UpdateHealthIndicator();
			this->Respawn();
		}
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
	CheckCharacterFall();
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
	else {
		this->gunsIgnored.Add(gun);
		this->MoveIgnoreActorAdd(gun);
	}
}

void ABlooPaperCharacter::DropGun() 
{
	if (this->attachedGun != NULL) {
		this->attachedGun->SetDetached();
		FVector newGunLocation = this->attachedGun->GetActorLocation();
		switch (this->facingDirection) {
			case FACING_DIRECTION::LEFT:
				newGunLocation.Y += 50;
				break;
			case FACING_DIRECTION::RIGHT:
				newGunLocation.Y -= 50;
				break;
		}
		this->attachedGun->SetActorLocation(newGunLocation);
		this->attachedGun = NULL;
		for (int i = 0; i < this->gunsIgnored.Num(); i++) {
			this->MoveIgnoreActorRemove(this->gunsIgnored[i]);
		}
		this->gunsIgnored.Empty();
	}
}

bool ABlooPaperCharacter::HasGun() {
	return this->attachedGun != NULL;
}

void ABlooPaperCharacter::Fire() {
	if (this->attachedGun != NULL) {
		this->attachedGun->Fire();
	}
}

void ABlooPaperCharacter::TakeDamage(float damageCount) 
{
	this->currentLifeSize -= damageCount;
	this->UpdateHealthIndicator();
	if (this->currentLifeSize <= 0) {
		this->currentLives--;
		this->UpdateHealthIndicator();
		if (this->currentLives == 0) {
			this->Die();
		}
		else {
			this->currentLifeSize = this->lifeSize;
			this->DropGun();
			this->UpdateHealthIndicator();
			this->Respawn();
		}
	}
}

void ABlooPaperCharacter::Die() {
	this->DropGun();
	this->Destroy();
}