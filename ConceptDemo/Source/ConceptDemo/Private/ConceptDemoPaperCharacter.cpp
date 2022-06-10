// Fill out your copyright notice in the Description page of Project Settings.


#include "ConceptDemoPaperCharacter.h"

#include "Guns/Gun.h"
#include "SpikesObject.h"
#include "Train/TrainAI.h"
#include <PaperFlipbookComponent.h>

#include "SemiSolidPlatform.h"
#include "Characters/Skull.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Props/Death/DeathIndicator.h"

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

	this->SpecialPowerLoadTime = 500;
	this->CurrentSpecialPowerLoadTime = 0;

	this->PlayerName = FText::FromString("Player");
	
	this->GetCharacterMovement()->JumpZVelocity = 700;
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	this->GetCharacterMovement()->GravityScale = 3;
	this->GetCharacterMovement()->JumpZVelocity = 1190;

	this->Immune = false;
	this->TimeBetweenActorRespawnBlink = 0.15;
	this->RespawnBlinkCount = 20;
	
	static ConstructorHelpers::FClassFinder<ADeathIndicator> DeathIndicatorObject(TEXT("/Game/Props/Death/DeathIndicator"));
	this->DeathIndicatorType = DeathIndicatorObject.Class;
	static ConstructorHelpers::FClassFinder<APowerupReadyProp> PowerUpReadyObject(TEXT("/Game/Props/VFX/CharacterPowerupReady/PowerupReady"));
	this->PowerUpReadyPropType = PowerUpReadyObject.Class;
	
	this->RelativeGunAttachLocation = FVector(-5, -30, -30);
	this->RelativeGunDropDistance = 150;

	this->DamageLevel2Threshold = 0.35;

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
		FVector GunLocation = this->GetActorLocation();
		GunLocation.X += this->RelativeGunAttachLocation.X;
		GunLocation.Z += this->RelativeGunAttachLocation.Z;
		if (this->AttachedGun->FacingDirection == EFacing_Direction::Left)
		{
			GunLocation.Y += this->RelativeGunAttachLocation.Y;
		}
		else if (this->AttachedGun->FacingDirection == EFacing_Direction::Right)
		{
			GunLocation.Y -= this->RelativeGunAttachLocation.Y;
		}
		this->AttachedGun->SetActorLocation(GunLocation);
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

void AUConceptDemoPaperCharacter::BindInputs()
{
	if (this->InputComponent)
	{
		this->InputComponent->BindAxis(TEXT("C HorizontalMovement"), this, &AUConceptDemoPaperCharacter::HandleMovement);
		this->InputComponent->BindAction(TEXT("C Jump"), IE_Pressed, this, &AUConceptDemoPaperCharacter::Jump);
		this->InputComponent->BindAction(TEXT("C Drop Down"), IE_Pressed, this, &AUConceptDemoPaperCharacter::DropDown);
		this->InputComponent->BindAxis(TEXT("C Fire"), this, &AUConceptDemoPaperCharacter::FireAxis);
		this->InputComponent->BindAction(TEXT("C Drop Gun"), IE_Pressed, this, &AUConceptDemoPaperCharacter::DropGun);
		this->InputComponent->BindAction(TEXT("C Use Power"), IE_Pressed, this, &AUConceptDemoPaperCharacter::UsePower);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5, FColor::Red, "ICNotSet");
	}
}

void AUConceptDemoPaperCharacter::UpdateFlipBooks()
{
	if (this->CurrentLifeSize > this->DamageLevel2Threshold)
	{
		if (this->IdleFlipBookDamageLevel1) this->IdleFlipBook = this->IdleFlipBookDamageLevel1;
		if (this->JumpingFlipBookDamageLevel1) this->JumpingFlipBook = this->JumpingFlipBookDamageLevel1;
		if (this->MovingFlipBookDamageLevel1) this->MovingFlipBook = this->MovingFlipBookDamageLevel1;
	}
	else
	{
		if (this->IdleFlipBookDamageLevel2) this->IdleFlipBook = this->IdleFlipBookDamageLevel2;
		if (this->JumpingFlipBookDamageLevel2) this->JumpingFlipBook = this->JumpingFlipBookDamageLevel2;
		if (this->MovingFlipBookDamageLevel2) this->MovingFlipBook = this->MovingFlipBookDamageLevel2;
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
			this->CharacterHUD->SetGunAttached(false);
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(564564, 2, FColor::Red, "HealthHUD not found!");
	}
	this->UpdateFlipBooks();
}

void AUConceptDemoPaperCharacter::MakeFallingDeathWithIndicator()
{
	const FTransform Transform = this->GetActorTransform();
	ADeathIndicator* DeathIndicator = this->GetWorld()->SpawnActorDeferred<ADeathIndicator>(this->DeathIndicatorType, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	this->bFallingDeath = true;
	DeathIndicator->DeadCharacter = this;
	UGameplayStatics::FinishSpawningActor(DeathIndicator, Transform);
}

void AUConceptDemoPaperCharacter::MakeFallingDeath()
{
	this->bFallingDeath = true;
	FVector CurrentPosition = this->GetActorLocation();
	CurrentPosition.X -= 500;
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
		if (this->AttachedGun == nullptr)
		{
			this->CharacterHUD->SetStaminaBar(this->SpecialPowerLoadTime, this->CurrentSpecialPowerLoadTime);
		}
	}
}

void AUConceptDemoPaperCharacter::Respawn()
{
	if (this->RespawnSound) UGameplayStatics::SpawnSound2D(this->GetWorld(), this->RespawnSound);
	this->SetActorHiddenInGame(false);
	this->Immune = true;
	if (this->AttachedGun != nullptr) {
		AGun* Gun = this->AttachedGun;
		this->DropGun();
		Gun->Respawn();
	}
	this->bFallingDeath = false;
	this->SetActorLocation(this->InitialPosition);
	this->GetWorld()->GetTimerManager().SetTimer(
		this->RespawnTimer, this, &AUConceptDemoPaperCharacter::ProcessRespawning, this->TimeBetweenActorRespawnBlink, true
	);
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
		this->CharacterHUD->SetGunAttached(true);
		this->CharacterHUD->SetStaminaBar(Gun->ShotsCount, Gun->ShotsLeft);
		this->AttachedGun->ShotLost.AddDynamic(this, &AUConceptDemoPaperCharacter::UpdateShotsCount);
		if (this->AttachGunSound) UGameplayStatics::SpawnSound2D(this->GetWorld(), this->AttachGunSound);
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
		this->CharacterHUD->SetGunAttached(false);
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
			NewGunLocation.Y += this->RelativeGunDropDistance;
			break;
		case EFacing_Direction::Right:
			NewGunLocation.Y -= this->RelativeGunDropDistance;
			break;
		}
		this->AttachedGun->SetActorLocation(NewGunLocation);
		this->AttachedGun->ShotLost.RemoveDynamic(this, &AUConceptDemoPaperCharacter::UpdateShotsCount);
		this->AttachedGun = nullptr;
		for (int i = 0; i < this->GunsIgnored.Num(); i++) {
			this->MoveIgnoreActorRemove(this->GunsIgnored[i]);
		}
		this->GunsIgnored.Empty();
		this->CharacterHUD->SetGunAttached(false);
	}
}

bool AUConceptDemoPaperCharacter::HasGun() const
{
	return this->AttachedGun != nullptr;
}

void AUConceptDemoPaperCharacter::Fire()
{
	if (IsValid(this->AttachedGun))
	{
		this->AttachedGun->Fire();
		this->CurrentSpecialPowerLoadTime = 0;
	}
	if (IsValid(this->AttachedGun))
	{
		this->CharacterHUD->SetStaminaBar(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}

void AUConceptDemoPaperCharacter::FireAxis(const float AxisValue)
{
	if (AxisValue > 0) this->Fire();
}

void AUConceptDemoPaperCharacter::UsePower()
{
	this->CurrentSpecialPowerLoadTime = 0;
	UGameplayStatics::SpawnSound2D(this->GetWorld(), this->PowerSound);
	this->SpecialPowerReadyPropShown = false;
}

void AUConceptDemoPaperCharacter::UpdateShotsCount()
{
	if (this->AttachedGun && this->CharacterHUD)
	{
		this->CharacterHUD->SetStaminaBar(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}


void AUConceptDemoPaperCharacter::TakeDamage(const float DamageCount)
{
	if (!this->Immune)
	{
		this->CurrentLifeSize -= DamageCount;
		this->UpdateHealthIndicator();
		if (this->CurrentLifeSize <= 0) {
			this->UpdateHealthIndicator();
			this->GetWorld()->SpawnActor<ASkull>(this->DeathSkull, this->GetActorLocation(), this->GetActorRotation());
			this->CurrentLifeSize = this->LifeSize;
			this->DropGun();
			this->UpdateHealthIndicator();
			this->SetActorHiddenInGame(true);
			this->MakeFallingDeath();
		}
		UGameplayStatics::SpawnSound2D(this->GetWorld(), this->DamageReceivedSound);
		this->UpdateFlipBooks();
	}
}

void AUConceptDemoPaperCharacter::AddLife(const float Life)
{
	if (this->CurrentLifeSize + Life < 1)
	{
		this->CurrentLifeSize += Life;
	}
	else
	{
		this->CurrentLifeSize = 1;
	}
	this->UpdateHealthIndicator();
	this->UpdateFlipBooks();
}

void AUConceptDemoPaperCharacter::ProcessRespawning()
{
	this->SetActorHiddenInGame(!this->IsHidden());
	this->CurrentHideAndShowCount++;
	if (this->CurrentHideAndShowCount >= this->RespawnBlinkCount)
	{
		this->CurrentHideAndShowCount = 0;
		this->Immune = false;
		this->SetActorHiddenInGame(false);
		this->GetWorld()->GetTimerManager().ClearTimer(this->RespawnTimer);
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
	if (this->AttachedGun == nullptr && this->CurrentSpecialPowerLoadTime < this->SpecialPowerLoadTime)
	{
		this->CurrentSpecialPowerLoadTime++;
		this->UpdateHealthIndicator();
	}
	if (CurrentSpecialPowerLoadTime >= this->SpecialPowerLoadTime)
	{
		if (!this->SpecialPowerReadyPropShown)
		{
			const FVector PowerUpReadyPropPosition = this->GetActorLocation();
			FTransform Transform = this->GetTransform();
			Transform.SetLocation(PowerUpReadyPropPosition);
			APowerupReadyProp* PowerUpReadyProp = this->GetWorld()->SpawnActorDeferred<APowerupReadyProp>(
				this->PowerUpReadyPropType, Transform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
			PowerUpReadyProp->ActorToFollow = this;
			UGameplayStatics::FinishSpawningActor(PowerUpReadyProp, Transform);
			this->SpecialPowerReadyPropShown = true;
		}
	}
}

void AUConceptDemoPaperCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp)
	{
		const ASpikesObject* Spikes = Cast<ASpikesObject>(OtherActor);
		const ATrainAI* Train = Cast<ATrainAI>(OtherActor);
		AGun* Gun = Cast<AGun>(OtherActor);
		if (Spikes)
		{
			this->MakeFallingDeathWithIndicator();
		}
		if (Train)
		{
			this->MakeFallingDeathWithIndicator();
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

