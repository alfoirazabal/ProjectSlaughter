// Fill out your copyright notice in the Description page of Project Settings.


#include "ConceptDemoPaperCharacter.h"

#include "Gun.h"
#include "SpikesObject.h"
#include "Train/TrainAI.h"
#include <PaperFlipbookComponent.h>

#include "SemiSolidPlatform.h"
#include "Characters/Skull.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

constexpr float GDefault_Character_Plane_X_Position = 760;

// Sets default values for this component's properties
AUConceptDemoPaperCharacter::AUConceptDemoPaperCharacter()
{
	this->AttachedGun = nullptr;

	this->Lives = 3;
	this->LifeSize = 1;

	this->CurrentLives = this->Lives;
	this->CurrentLifeSize = this->LifeSize;

	this->InitialPosition = FVector::ZeroVector;
	this->bFallingDeath = false;

	this->PlayerName = FText::FromString("Player");
	
	this->GetCharacterMovement()->JumpZVelocity = 700;

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(38.59, 89.37);
	this->TriggerCapsule->SetCollisionProfileName("Trigger");
	this->TriggerCapsule->SetupAttachment(this->RootComponent);

	this->TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AUConceptDemoPaperCharacter::OnOverlapBegin);
	this->TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AUConceptDemoPaperCharacter::OnOverlapEnd);
}

void AUConceptDemoPaperCharacter::MoveGun() const
{
	if (this->AttachedGun != nullptr) {
		this->AttachedGun->FacingDirection = this->FacingDirection;
		FVector ActorLocation = this->GetActorLocation();
		ActorLocation.Z += this->GunZRelativeLocation;
		this->AttachedGun->SetActorLocation(ActorLocation);
	}
}

void AUConceptDemoPaperCharacter::CheckCharacterFall()
{
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

void AUConceptDemoPaperCharacter::EnsureXAxisLocation()
{
	// Prevents actor from moving along the X axis, and move only along the Y and Z axis of the simulated 3D plane.
	FVector CurrentPosition = this->GetActorLocation();
	if (!this->bFallingDeath && CurrentPosition.X != GDefault_Character_Plane_X_Position) {
		CurrentPosition.X = GDefault_Character_Plane_X_Position;
		this->SetActorLocation(CurrentPosition);
	}
}

// Called when the game starts
void AUConceptDemoPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->InitialPosition = this->GetActorLocation();
	TArray<UActorComponent*> Components;
	this->GetComponents(Components);
	const UWidgetComponent* WidgetComponent = nullptr;
	for (int i = 0; WidgetComponent == nullptr && i < Components.Num(); i++) {
		WidgetComponent = Cast<UWidgetComponent>(Components[i]);
	}
	if (WidgetComponent) {
		UUserWidget* HUDWidget = WidgetComponent->GetWidget();
		this->CharacterHUD = Cast<UPaperCharacterHUD>(HUDWidget);
		if (!this->CharacterHUD) {
			GEngine->AddOnScreenDebugMessage(5345343, 2, FColor::Red, "Unable to cast HealthHUD for PaperCharacter!");
		}
		else
		{
			this->CharacterHUD->SetNoGun();
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(564564, 2, FColor::Red, "HealthHUD not found!");
	}
}

void AUConceptDemoPaperCharacter::MakeFallingDeath()
{
	this->bFallingDeath = true;
	FVector CurrentPosition = this->GetActorLocation();
	CurrentPosition.X -= 250;
	this->SetActorLocation(CurrentPosition);
}

void AUConceptDemoPaperCharacter::SetPlayerName(const FText NewPlayerName) const
{
	if (this->CharacterHUD)
	{
		this->CharacterHUD->SetPlayerName(NewPlayerName);
	}
}

void AUConceptDemoPaperCharacter::UpdateHealthIndicator() const
{
	if (this->CharacterHUD) {
		this->CharacterHUD->SetHealth(this->CurrentLifeSize);
		this->CharacterHUD->SetLives(this->CurrentLives);
	}
}

void AUConceptDemoPaperCharacter::Respawn()
{
	if (this->AttachedGun != nullptr) {
		AGun* Gun = this->AttachedGun;
		this->DropGun();
		Gun->Respawn();
	}
	this->bFallingDeath = false;
	this->SetActorLocation(this->InitialPosition);
}



bool AUConceptDemoPaperCharacter::IsOnTheAir() const
{
	const FVector Velocity = this->GetVelocity();
	const float ZVelocity = Velocity.Z;
	return ZVelocity != 0;
}

FRotator AUConceptDemoPaperCharacter::GetRightRotator()
{
	const FRotator Rotator = FRotator::ZeroRotator;
	return Rotator;
}

FRotator AUConceptDemoPaperCharacter::GetLeftRotator()
{
	FRotator Rotator = FRotator::ZeroRotator;
	Rotator.Yaw = 180;
	return Rotator;
}

void AUConceptDemoPaperCharacter::HandleMovement(const float ScaleValue)
{
	FVector Vector = FVector::ZeroVector;
	Vector.Y = 1;
	AddMovementInput(Vector, ScaleValue);
	MoveGun();
	UPaperFlipbookComponent* sprite = GetSprite();
	if (IsOnTheAir()) {
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

void AUConceptDemoPaperCharacter::DropDown()
{
	FFindFloorResult FloorResult = this->GetCharacterMovement()->CurrentFloor;
	FHitResult HitResult = FloorResult.HitResult;
	AActor* FloorActor = HitResult.GetActor();
	if (FloorActor)
	{
		ASemiSolidPlatform* SemiSolidPlatform = Cast<ASemiSolidPlatform>(FloorActor);
		if (SemiSolidPlatform)
		{
			FVector CurrentPosition = this->GetActorLocation();
			CurrentPosition.Z -= 10;
			this->SetActorLocation(CurrentPosition);
			this->MoveIgnoreActorAdd(SemiSolidPlatform);
		}
	}
}

void AUConceptDemoPaperCharacter::Jump()
{
	if (this->GetCharacterMovement()->Velocity.Z == 0) UGameplayStatics::PlaySound2D(this->GetWorld(), this->JumpSound);
	Super::Jump();
}

void AUConceptDemoPaperCharacter::AttachGun(AGun* Gun)
{
	if (this->AttachedGun == nullptr) {
		this->AttachedGun = Gun;
		this->AttachedGun->SetAttached();
		this->CharacterHUD->SetShotsLeft(Gun->ShotsCount, Gun->ShotsLeft);
		this->AttachedGun->ShotLost.AddDynamic(this, &AUConceptDemoPaperCharacter::UpdateShotsCount);
	}
	else {
		this->GunsIgnored.Add(Gun);
		this->MoveIgnoreActorAdd(Gun);
	}
}

void AUConceptDemoPaperCharacter::DropGun()
{
	if (this->AttachedGun != nullptr) {
		this->AttachedGun->SetDetached();
		FVector NewGunLocation;
		if (this->bFallingDeath)
		{
			NewGunLocation = this->AttachedGun->InitialLocation;
		}
		else
		{
			NewGunLocation = this->AttachedGun->GetActorLocation();
		}
		switch (this->FacingDirection) {
		case EFacing_Direction::Left:
			NewGunLocation.Y += 125;
			break;
		case EFacing_Direction::Right:
			NewGunLocation.Y -= 125;
			break;
		}
		this->AttachedGun->SetActorLocation(NewGunLocation);
		this->AttachedGun->ShotLost.RemoveDynamic(this, &AUConceptDemoPaperCharacter::UpdateShotsCount);
		this->AttachedGun = nullptr;
		for (int i = 0; i < this->GunsIgnored.Num(); i++) {
			this->MoveIgnoreActorRemove(this->GunsIgnored[i]);
		}
		this->GunsIgnored.Empty();
		this->CharacterHUD->SetNoGun();
	}
}

bool AUConceptDemoPaperCharacter::HasGun() const
{
	return this->AttachedGun != nullptr;
}

void AUConceptDemoPaperCharacter::Fire()
{
	if (IsValid(this->AttachedGun)) {
		this->AttachedGun->Fire();
	}
	if (IsValid(this->AttachedGun))
	{
		this->CharacterHUD->SetShotsLeft(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}

void AUConceptDemoPaperCharacter::UpdateShotsCount()
{
	if (this->AttachedGun && this->CharacterHUD)
	{
		this->CharacterHUD->SetShotsLeft(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}


void AUConceptDemoPaperCharacter::TakeDamage(float DamageCount)
{
	this->CurrentLifeSize -= DamageCount;
	this->UpdateHealthIndicator();
	if (this->CurrentLifeSize <= 0) {
		this->CurrentLives--;
		this->UpdateHealthIndicator();
		this->GetWorld()->SpawnActor<ASkull>(this->DeathSkull, this->GetActorLocation(), this->GetActorRotation());
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

void AUConceptDemoPaperCharacter::Die()
{
	this->DropGun();
	this->PlayerDeath.Broadcast();
	this->Destroy();
}


// Called every frame
void AUConceptDemoPaperCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	EnsureXAxisLocation();
}

void AUConceptDemoPaperCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp)
	{
		ABullet* Bullet = Cast<ABullet>(OtherActor);
		const ASpikesObject* Spikes = Cast<ASpikesObject>(OtherActor);
		const ATrainAI* Train = Cast<ATrainAI>(OtherActor);
		AGun* Gun = Cast<AGun>(OtherActor);
		if (Bullet)
		{
			if (
				(this->AttachedGun != nullptr && Bullet->FireSource != nullptr && Bullet->FireSource != this->AttachedGun) ||
				this->AttachedGun == nullptr
			) {
				Bullet->Destroy();
				this->TakeDamage(Bullet->BulletDamage);
			}
		}
		if (Spikes)
		{
			this->MakeFallingDeath();
		}
		if (Train)
		{
			this->MakeFallingDeath();
		}
		if (Gun)
		{
			if (!this->HasGun())
			{
				this->AttachGun(Gun);
			}
			else
			{
				this->MoveIgnoreActorAdd(Gun);
			}
		}
	}
}

void AUConceptDemoPaperCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp)
	{
		AGun* Gun = Cast<AGun>(OtherActor);
		if (Gun)
		{
			if (this->HasGun())
			{
				this->MoveIgnoreActorRemove(Gun);
			}
		}
	}
}

