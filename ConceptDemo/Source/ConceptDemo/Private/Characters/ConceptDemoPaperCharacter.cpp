// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ConceptDemoPaperCharacter.h"

#include "Guns/Gun.h"
#include "Props/SpikesObject.h"
#include "Train/TrainAI.h"
#include <PaperFlipbookComponent.h>

#include "Characters/PowerupReadyIndicator.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Props/Death/DeathIndicator.h"
#include "Props/Platforms/SemiSolidPlatform.h"

// Sets default values for this component's properties
AConceptDemoPaperCharacter::AConceptDemoPaperCharacter()
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
	
	this->GetCharacterMovement()->GravityScale = 3;
	this->GetCharacterMovement()->JumpZVelocity = 1190;

	this->Immune = false;
	this->TimeBetweenActorRespawnBlink = 0.15;
	this->RespawnBlinkCount = 20;
	
	static ConstructorHelpers::FClassFinder<ADeathIndicator> DeathIndicatorObject(TEXT("/Game/Props/Death/DeathIndicator"));
	this->DeathIndicatorType = DeathIndicatorObject.Class;
	static ConstructorHelpers::FClassFinder<APowerupReadyProp> PowerUpReadyObject(TEXT("/Game/Props/VFX/CharacterPowerupReady/PowerupReady"));
	this->PowerUpReadyPropType = PowerUpReadyObject.Class;
	static ConstructorHelpers::FObjectFinder<USoundBase> PowerUpReadySoundObject(TEXT("/Game/Character/Sounds/AbilityReady"));
	this->PowerUpReadySound = PowerUpReadySoundObject.Object;
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone1OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone1"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone2OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone2"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBloodSplat1ClassFinder(TEXT("/Game/Character/Droppables/DroppableBloodSplat1"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBloodSplat2ClassFinder(TEXT("/Game/Character/Droppables/DroppableBloodSplat2"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBloodSplat3ClassFinder(TEXT("/Game/Character/Droppables/DroppableBloodSplat3"));
	this->DroppableTypes.Add(DroppableBone1OClassFinder.Class);
	this->DroppableTypes.Add(DroppableBone2OClassFinder.Class);
	this->DroppableTypes.Add(DroppableBloodSplat1ClassFinder.Class);
	this->DroppableTypes.Add(DroppableBloodSplat2ClassFinder.Class);
	this->DroppableTypes.Add(DroppableBloodSplat3ClassFinder.Class);
	this->PowerUpReadyIndicatorRelativeLocation = FVector(-70, 0, 130);
	
	this->RelativeGunAttachLocation = FVector(-5, -30, -30);
	this->RelativeGunDropDistance = 150;

	this->DamageLevel2Threshold = 0.35;

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(38.59, 89.37);
	this->TriggerCapsule->SetCollisionProfileName("Trigger");
	this->TriggerCapsule->SetupAttachment(this->RootComponent);

	this->TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AConceptDemoPaperCharacter::OnOverlapBegin);
	this->TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AConceptDemoPaperCharacter::OnOverlapEnd);
}

void AConceptDemoPaperCharacter::MoveGun() const
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

void AConceptDemoPaperCharacter::BindInputs()
{
	if (this->InputComponent)
	{
		this->InputComponent->BindAxis(TEXT("C HorizontalMovement"), this, &AConceptDemoPaperCharacter::HandleMovement);
		this->InputComponent->BindAction(TEXT("C Jump"), IE_Pressed, this, &AConceptDemoPaperCharacter::Jump);
		this->InputComponent->BindAction(TEXT("C Drop Down"), IE_Pressed, this, &AConceptDemoPaperCharacter::DropDown);
		this->InputComponent->BindAxis(TEXT("C Fire"), this, &AConceptDemoPaperCharacter::FireAxis);
		this->InputComponent->BindAction(TEXT("C Drop Gun"), IE_Pressed, this, &AConceptDemoPaperCharacter::DropGun);
		this->InputComponent->BindAction(TEXT("C Use Power"), IE_Pressed, this, &AConceptDemoPaperCharacter::UsePower);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5, FColor::Red, "ICNotSet");
	}
}

void AConceptDemoPaperCharacter::UpdateFlipBooks()
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
void AConceptDemoPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->InitialPosition = this->GetActorLocation();
	this->UpdateFlipBooks();
}

void AConceptDemoPaperCharacter::MakeFallingDeathWithIndicator()
{
	const FTransform Transform = this->GetActorTransform();
	ADeathIndicator* DeathIndicator = this->GetWorld()->SpawnActorDeferred<ADeathIndicator>(this->DeathIndicatorType, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	this->bFallingDeath = true;
	DeathIndicator->DeadCharacter = this;
	UGameplayStatics::FinishSpawningActor(DeathIndicator, Transform);
}

void AConceptDemoPaperCharacter::MakeFallingDeath()
{
	this->bFallingDeath = true;
	FVector CurrentPosition = this->GetActorLocation();
	CurrentPosition.X -= 500;
	this->SetActorLocation(CurrentPosition);
}

void AConceptDemoPaperCharacter::UpdateHealthIndicator() const
{
	if (this->UserWidgetPlayersStatusControl) {
		this->UserWidgetPlayersStatusControl->SetHealth(this->CurrentLifeSize);
		this->UserWidgetPlayersStatusControl->SetLives(this->CurrentLives);
		if (this->AttachedGun == nullptr)
		{
			this->UserWidgetPlayersStatusControl->SetStaminaBar(this->SpecialPowerLoadTime, this->CurrentSpecialPowerLoadTime);
		}
	}
}

void AConceptDemoPaperCharacter::Respawn()
{
	this->UpdateFlipBooks();
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
		this->RespawnTimer, this, &AConceptDemoPaperCharacter::ProcessRespawning, this->TimeBetweenActorRespawnBlink, true
	);
}

void AConceptDemoPaperCharacter::HandleMovement(const float ScaleValue)
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

void AConceptDemoPaperCharacter::CheckCharacterFall()
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

void AConceptDemoPaperCharacter::DropDown()
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

void AConceptDemoPaperCharacter::Jump()
{
	if (this->GetCharacterMovement()->Velocity.Z == 0) UGameplayStatics::PlaySound2D(this->GetWorld(), this->JumpSound);
	Super::Jump();
}


void AConceptDemoPaperCharacter::AttachGun(AGun* Gun)
{
	if (this->AttachedGun == nullptr) {
		this->AttachedGun = Gun;
		this->AttachedGun->SetAttached();
		this->UserWidgetPlayersStatusControl->SetGunAttached(true);
		this->UserWidgetPlayersStatusControl->SetStaminaBar(Gun->ShotsCount, Gun->ShotsLeft);
		this->AttachedGun->ShotLost.AddDynamic(this, &AConceptDemoPaperCharacter::UpdateShotsCount);
		if (this->AttachGunSound) UGameplayStatics::SpawnSound2D(this->GetWorld(), this->AttachGunSound);
	}
	else {
		this->GunsIgnored.Add(Gun);
		this->MoveIgnoreActorAdd(Gun);
	}
}

void AConceptDemoPaperCharacter::DropGun()
{
	if (this->AttachedGun != nullptr) {
		this->AttachedGun->SetDetached();
		this->UserWidgetPlayersStatusControl->SetGunAttached(false);
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
			default:
				break;
		}
		this->AttachedGun->SetActorLocation(NewGunLocation);
		this->AttachedGun->ShotLost.RemoveDynamic(this, &AConceptDemoPaperCharacter::UpdateShotsCount);
		this->AttachedGun = nullptr;
		for (int i = 0; i < this->GunsIgnored.Num(); i++) {
			this->MoveIgnoreActorRemove(this->GunsIgnored[i]);
		}
		this->GunsIgnored.Empty();
		this->UserWidgetPlayersStatusControl->SetGunAttached(false);
	}
}

bool AConceptDemoPaperCharacter::HasGun() const
{
	return this->AttachedGun != nullptr;
}

void AConceptDemoPaperCharacter::Fire()
{
	if (IsValid(this->AttachedGun))
	{
		this->AttachedGun->Fire(this);
		this->CurrentSpecialPowerLoadTime = 0;
	}
	if (IsValid(this->AttachedGun))
	{
		this->UserWidgetPlayersStatusControl->SetStaminaBar(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}

void AConceptDemoPaperCharacter::FireAxis(const float AxisValue)
{
	if (AxisValue > 0) this->Fire();
}

void AConceptDemoPaperCharacter::UsePower()
{
	this->CurrentSpecialPowerLoadTime = 0;
	UGameplayStatics::SpawnSound2D(this->GetWorld(), this->PowerSound);
	if (this->CurrentPowerUpReadyIndicator)
	{
		this->CurrentPowerUpReadyIndicator->Destroy();
		this->CurrentPowerUpReadyIndicator = nullptr;
	}
	this->SpecialPowerReadyPropShown = false;
}

void AConceptDemoPaperCharacter::UpdateShotsCount()
{
	if (this->AttachedGun && this->UserWidgetPlayersStatusControl)
	{
		this->UserWidgetPlayersStatusControl->SetStaminaBar(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}

void AConceptDemoPaperCharacter::TakeDamage(const float DamageCount)
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
		if (this->DroppableTypes.Num() > 0)
		{
			const TSubclassOf<ADroppable> RandomDroppable = this->DroppableTypes[FMath::RandRange(0, this->DroppableTypes.Num() - 1)];
			this->GetWorld()->SpawnActor<ADroppable>(RandomDroppable, this->GetActorLocation(), this->GetActorRotation());
		}
		UGameplayStatics::SpawnSound2D(this->GetWorld(), this->DamageReceivedSound);
		this->UpdateFlipBooks();
	}
}

void AConceptDemoPaperCharacter::AddLife(const float Life)
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

void AConceptDemoPaperCharacter::ProcessRespawning()
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

void AConceptDemoPaperCharacter::Die()
{
	this->DropGun();
	this->PlayerDeath.Broadcast();
	this->Destroy();
}

// Called every frame
void AConceptDemoPaperCharacter::Tick(const float DeltaTime)
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
			if (this->PowerUpReadyPropType)
			{
				APowerupReadyProp* PowerUpReadyProp = this->GetWorld()->SpawnActorDeferred<APowerupReadyProp>(
					this->PowerUpReadyPropType, Transform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn
				);
				PowerUpReadyProp->ActorToFollow = this;
				UGameplayStatics::FinishSpawningActor(PowerUpReadyProp, Transform);
			}
			UGameplayStatics::SpawnSound2D(this->GetWorld(), this->PowerUpReadySound);
			if (!this->CurrentPowerUpReadyIndicator && this->PowerUpReadyIndicatorType)
			{
				if (this->PowerUpReadyIndicatorFlipBook)
				{
					APowerupReadyIndicator* PowerUpReadyIndicator = this->GetWorld()->SpawnActorDeferred<APowerupReadyIndicator>(
						this->PowerUpReadyIndicatorType, Transform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn
					);
					PowerUpReadyIndicator->FollowingActor = this;
					PowerUpReadyIndicator->FollowingRelativePosition = this->PowerUpReadyIndicatorRelativeLocation;
					PowerUpReadyIndicator->GetRenderComponent()->SetFlipbook(this->PowerUpReadyIndicatorFlipBook);
					UGameplayStatics::FinishSpawningActor(PowerUpReadyIndicator, Transform);
					this->CurrentPowerUpReadyIndicator = PowerUpReadyIndicator;
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(FMath::Rand(), 6, FColor::Red, "PowerUp Ready Indicator FlipBook unset for: " + this->GetName());
				}
			}
			this->SpecialPowerReadyPropShown = true;
		}
	}
}

void AConceptDemoPaperCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

void AConceptDemoPaperCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

