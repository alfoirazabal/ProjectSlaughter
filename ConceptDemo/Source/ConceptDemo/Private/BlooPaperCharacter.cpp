// Fill out your copyright notice in the Description page of Project Settings.

#include "BlooPaperCharacter.h"
#include "Gun.h"
#include "SpikesObject.h"
#include "Train/TunnelGateAI.h"
#include "Train/TrainAI.h"
#include <PaperFlipbookComponent.h>

constexpr float GDefault_Character_Plane_X_Position = 760;

ABlooPaperCharacter::ABlooPaperCharacter() {
	const ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleFlipBookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_idle_Flipbook.Bloo_idle_Flipbook"));
	const ConstructorHelpers::FObjectFinder<UPaperFlipbook> MovingFlipBookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_moving.Bloo_moving"));
	const ConstructorHelpers::FObjectFinder<UPaperFlipbook> JumpingFlipBookObject(TEXT("/Game/Character/Bloo/Images/Flipbooks/Bloo_jumping_Flipbook.Bloo_jumping_Flipbook"));
	this->IdleFlipBook = IdleFlipBookObject.Object;
	this->MovingFlipBook = MovingFlipBookObject.Object;
	this->JumpingFlipBook = JumpingFlipBookObject.Object;
	this->AttachedGun = nullptr;

	this->Lives = 3;
	this->LifeSize = 1;

	this->CurrentLives = this->Lives;
	this->CurrentLifeSize = this->LifeSize;

	this->InitialPosition = FVector::ZeroVector;
	this->bFallingDeath = false;

	this->BlooHealthHUD = nullptr;
}

void ABlooPaperCharacter::BeginPlay() {
	Super::BeginPlay();
	this->InitialPosition = this->GetActorLocation();
	TArray<UActorComponent*> Components;
	this->GetComponents(Components);
	const UWidgetComponent* HealthHUDWidgetComponent = nullptr;
	for (int i = 0; HealthHUDWidgetComponent == nullptr && i < Components.Num(); i++) {
		HealthHUDWidgetComponent = Cast<UWidgetComponent>(Components[i]);
	}
	if (HealthHUDWidgetComponent) {
		GEngine->AddOnScreenDebugMessage(564564, 2, FColor::Cyan, HealthHUDWidgetComponent->GetName());
		UUserWidget* HealthHUDWidget = HealthHUDWidgetComponent->GetWidget();
		this->BlooHealthHUD = Cast<UBlooHealthHUD>(HealthHUDWidget);
		if (!this->BlooHealthHUD) {
			GEngine->AddOnScreenDebugMessage(5345343, 2, FColor::Red, "Unable to cast HealthHUD to BlooHealthHUD for BlooPaperCharacter!");
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(564564, 2, FColor::Red, "HealthHUD not found!");
	}
}

void ABlooPaperCharacter::MakeFallingDeath()
{
	this->bFallingDeath = true;
	FVector CurrentPosition = this->GetActorLocation();
	CurrentPosition.X -= 250;
	this->SetActorLocation(CurrentPosition);
}

void ABlooPaperCharacter::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TArray<AActor*> OverlappingActors;
	this->GetOverlappingActors(OverlappingActors);
	bool bTrainFound = false;
	bool bTunnelGateFound = false;
	for (int i = 0; i < OverlappingActors.Num(); i++) {
		ABullet* Bullet = Cast<ABullet>(OverlappingActors[i]);
		const ASpikesObject* Spikes = Cast<ASpikesObject>(OverlappingActors[i]);
		if (!bTrainFound) bTrainFound = Cast<ATrainAI>(OverlappingActors[i]) != nullptr;
		if (!bTunnelGateFound) bTunnelGateFound = Cast<ATunnelGateAI>(OverlappingActors[i]) != nullptr;
		if (Bullet) {
			if (
				(this->AttachedGun != nullptr && Bullet->FireSource != this->AttachedGun) ||
				this->AttachedGun == nullptr
			) {
				Bullet->Destroy();
				this->TakeDamage(0.1f);
			}
		}
		if (Spikes) {
			this->MakeFallingDeath();
		}
	}
	if (bTrainFound && bTunnelGateFound)
	{
		this->MakeFallingDeath();
	}
	EnsureXAxisLocation();
}

bool IsOnTheAir(const ABlooPaperCharacter* character) {
	const FVector Velocity = character->GetVelocity();
	const float ZVelocity = Velocity.Z;
	return ZVelocity != 0;
}

FRotator GetRightRotator() {
	const FRotator Rotator = FRotator::ZeroRotator;
	return Rotator;
}

FRotator GetLeftRotator() {
	FRotator Rotator = FRotator::ZeroRotator;
	Rotator.Yaw = 180;
	return Rotator;
}

void ABlooPaperCharacter::EnsureXAxisLocation() {
	// Prevents actor from moving along the X axis, and move only along the Y and Z axis of the simulated 3D plane.
	FVector CurrentPosition = this->GetActorLocation();
	if (!this->bFallingDeath && CurrentPosition.X != GDefault_Character_Plane_X_Position) {
		CurrentPosition.X = GDefault_Character_Plane_X_Position;
		this->SetActorLocation(CurrentPosition);
	}
}

void ABlooPaperCharacter::UpdateHealthIndicator() const
{
	if (this->BlooHealthHUD) {
		this->BlooHealthHUD->SetHealth(this->CurrentLifeSize);
		this->BlooHealthHUD->SetLives(this->CurrentLives);
	}
}

void ABlooPaperCharacter::Respawn() {
	if (this->AttachedGun != nullptr) {
		AGun* Gun = this->AttachedGun;
		this->DropGun();
		Gun->Respawn();
	}
	this->bFallingDeath = false;
	this->SetActorLocation(this->InitialPosition);
}

void ABlooPaperCharacter::CheckCharacterFall() {
	if (this->GetActorLocation().Z <= GLevelsZFallLimit) {
		this->CurrentLives--;
		this->CurrentLifeSize = this->LifeSize;
		if (this->CurrentLives == 0) {
			this->Die();
		}
		else {
			this->UpdateHealthIndicator();
			this->Respawn();
		}
	}
}

void ABlooPaperCharacter::MoveGun() const {
	if (this->AttachedGun != nullptr) {
		this->AttachedGun->FacingDirection = this->FacingDirection;
		this->AttachedGun->SetActorLocation(this->GetActorLocation());
	}
}

void ABlooPaperCharacter::HandleMovement(float ScaleValue) {
	FVector vector = FVector::ZeroVector;
	vector.Y = 1;
	AddMovementInput(vector, ScaleValue);
	MoveGun();
	UPaperFlipbookComponent* sprite = GetSprite();
	if (IsOnTheAir(this)) {
		sprite->SetFlipbook(this->JumpingFlipBook);
	}
	else {
		if (ScaleValue == 0) {
			sprite->SetFlipbook(this->IdleFlipBook);
		}
		else if (ScaleValue > 0) {
			sprite->SetFlipbook(this->MovingFlipBook);
			sprite->SetRelativeRotation(GetRightRotator());
			this->FacingDirection = EFacing_Direction::Right;
		}
		else if (ScaleValue < 0) {
			sprite->SetFlipbook(this->MovingFlipBook);
			sprite->SetRelativeRotation(GetLeftRotator());
			this->FacingDirection = EFacing_Direction::Left;
		}
	}
	CheckCharacterFall();
}

void ABlooPaperCharacter::HandleJump() {
	Jump();
}

void ABlooPaperCharacter::HandleStopJump() {
	StopJumping();
}

void ABlooPaperCharacter::AttachGun(AGun* Gun)
{
	if (this->AttachedGun == nullptr) {
		this->AttachedGun = Gun;
		this->AttachedGun->SetAttached();
	}
	else {
		this->GunsIgnored.Add(Gun);
		this->MoveIgnoreActorAdd(Gun);
	}
}

void ABlooPaperCharacter::DropGun() 
{
	if (this->AttachedGun != nullptr) {
		this->AttachedGun->SetDetached();
		FVector NewGunLocation = this->AttachedGun->GetActorLocation();
		switch (this->FacingDirection) {
			case EFacing_Direction::Left:
				NewGunLocation.Y += 50;
				break;
			case EFacing_Direction::Right:
				NewGunLocation.Y -= 50;
				break;
		}
		this->AttachedGun->SetActorLocation(NewGunLocation);
		this->AttachedGun = nullptr;
		for (int i = 0; i < this->GunsIgnored.Num(); i++) {
			this->MoveIgnoreActorRemove(this->GunsIgnored[i]);
		}
		this->GunsIgnored.Empty();
	}
}

bool ABlooPaperCharacter::HasGun() {
	return this->AttachedGun != nullptr;
}

void ABlooPaperCharacter::Fire() {
	if (this->AttachedGun != nullptr) {
		this->AttachedGun->Fire();
	}
}

void ABlooPaperCharacter::TakeDamage(const float DamageCount) 
{
	this->CurrentLifeSize -= DamageCount;
	this->UpdateHealthIndicator();
	if (this->CurrentLifeSize <= 0) {
		this->CurrentLives--;
		this->UpdateHealthIndicator();
		if (this->CurrentLives == 0) {
			this->Die();
		}
		else {
			this->CurrentLifeSize = this->LifeSize;
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