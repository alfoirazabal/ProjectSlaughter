// Fill out your copyright notice in the Description page of Project Settings.

#include "Guns/Gun.h"

#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

constexpr int GRotation_Time_DS = 150;

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bRotate = true;
	this->ShouldRotate = false;
	this->RotationSpeed = 1;
	this->TimeBetweenShots = 10;
	this->ShotsCount = 50;
	this->CurrentTimeBetweenShots = 0;
	this->ShotLossTime = 100;
	this->CurrentShotLossTime = this->ShotLossTime;
	this->ShotDamage = 0.035;

	this->BulletSpawnRelativeLocation = FVector(0.0f, 50.0f, 10.0f);

	this->BulletClass = nullptr;

	this->GunType = Common;

	static ConstructorHelpers::FObjectFinder<USoundWave> GunGrabObject(TEXT("/Game/Props/Guns/GunGrab"));
	this->GunGrabSound = GunGrabObject.Object;

	this->RelativeAttachedSize = FVector(0.8, 0.8, 0.8);

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(67.68, 67.68);
	this->TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	this->TriggerCapsule->SetupAttachment(this->RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	this->ShotsLeft = this->ShotsCount;
	this->InitialLocation = this->GetActorLocation();
	if (!this->SparklesType)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2, FColor::Yellow, "Sparkles not set fun gun: " + this->GetName());
	}
	this->SpawnSparkles();
}

void AGun::SpawnSparkles()
{
	if (this->SparklesType)
	{
		this->Sparkles =
			this->GetWorld()->SpawnActor<AActor>(this->SparklesType, GetActorLocation(), FRotator(90, 0, 90));
	}
}

void AGun::DestroySparkles() const
{
	if (this->Sparkles)
	{
		this->Sparkles->Destroy();
	}
}

// Called every frame
void AGun::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->ShouldRotate && this->bRotate) {
		const int RotationTime = (DeltaTime * GRotation_Time_DS) * RotationSpeed;
		FRotator Rotator = FRotator::ZeroRotator;
		Rotator.Yaw = RotationTime;
		AddActorLocalRotation(Rotator);
	}
	else {
		FRotator Rotator = FRotator::ZeroRotator;
		switch (this->FacingDirection) {
			case EFacing_Direction::Left:
				Rotator.Yaw = 270;
				break;
			case EFacing_Direction::Right:
				Rotator.Yaw = 90;
				break;
		}
		this->SetActorRotation(Rotator);
	}
	if (this->CurrentTimeBetweenShots > 0)
	{
		this->CurrentTimeBetweenShots--;
	}
	this->CurrentShotLossTime--;
	if (this->CurrentShotLossTime == 0)
	{
		this->CurrentShotLossTime = this->ShotLossTime;
		this->ShotsLeft--;
		this->ShotLost.Broadcast();
		if (this->ShotsLeft == 0)
		{
			this->GunDead.Broadcast(this);
			if (this->Sparkles)
			{
				this->Sparkles->Destroy();
			}
		}
	}
}

void AGun::SetAttached() {
	if (this->ShouldRotate) this->bRotate = false;
	this->SetActorEnableCollision(false);
	UGameplayStatics::SpawnSound2D(this->GetWorld(), this->GunGrabSound);
	this->DestroySparkles();
	this->SetActorScale3D(this->RelativeAttachedSize);
	this->OnGunAttatched();
}

void AGun::SetDetached() {
	if (this->ShouldRotate) this->bRotate = true;
	this->SetActorEnableCollision(true);
	FTimerHandle TimerHandle;
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGun::SpawnSparkles, 0.1, false);
	this->SetActorScale3D(FVector(1, 1, 1));
	this->OnGunDetached();
}

void AGun::Fire(AActor* SourceActor) {
	if (this->BulletClass != nullptr) {
		if (this->CurrentTimeBetweenShots == 0 && this->ShotsLeft > 0)
		{
			FVector bulletLocation = this->GetActorLocation();
			bulletLocation.Z += this->BulletSpawnRelativeLocation.Z;
			if (this->FacingDirection == EFacing_Direction::Left) {
				bulletLocation.Y -= this->BulletSpawnRelativeLocation.Y;
			}
			else if (this->FacingDirection == EFacing_Direction::Right) {
				bulletLocation.Y += this->BulletSpawnRelativeLocation.Y;
			}
			FTransform Transform = this->GetActorTransform();
			Transform.SetLocation(bulletLocation);
			ABullet* Bullet = this->GetWorld()->SpawnActorDeferred<ABullet>(this->BulletClass, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			Bullet->SourceActor = SourceActor;
			Bullet->SourceGun = this;
			Bullet->FacingDirection = this->FacingDirection;
			Bullet->TravelSpeed = 15;
			Bullet->MaxTravelDistance = 5000;
			Bullet->BulletDamage = this->ShotDamage;
			UGameplayStatics::FinishSpawningActor(Bullet, Transform);
			this->CurrentTimeBetweenShots = this->TimeBetweenShots;
			this->ShotsLeft--;
		}
		if (this->ShotsLeft == 0)
		{
			this->GunDead.Broadcast(this);
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(23425, 10, FColor::Red, "ERR: Bullet class unset for gun: " + this->GetName());
	}
}

void AGun::Respawn() {
	this->SetActorLocation(this->InitialLocation);
}
