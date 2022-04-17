// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "ConceptDemoPaperCharacter.h"
#include "Components/CapsuleComponent.h"

constexpr int GRotation_Time_DS = 150;

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bRotate = true;
	this->RotationSpeed = 1;

	this->BulletSpawnRelativeLocation = FVector(0.0f, 50.0f, 10.0f);

	this->BulletClass = nullptr;

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(67.68, 67.68);
	this->TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	this->TriggerCapsule->SetupAttachment(this->RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	this->InitialLocation = this->GetActorLocation();
}

// Called every frame
void AGun::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bRotate) {
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
}

void AGun::SetAttached() {
	this->bRotate = false;
	this->SetActorEnableCollision(false);
	this->SetActorScale3D(FVector(0.7f, 0.7f, 0.7f));
}

void AGun::SetDetached() {
	this->bRotate = true;
	this->SetActorEnableCollision(true);
	this->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void AGun::Fire() {
	if (this->BulletClass != nullptr) {
		FVector bulletLocation = this->GetActorLocation();
		bulletLocation.Z += this->BulletSpawnRelativeLocation.Z;
		if (this->FacingDirection == EFacing_Direction::Left) {
			bulletLocation.Y -= this->BulletSpawnRelativeLocation.Y;
		}
		else if (this->FacingDirection == EFacing_Direction::Right) {
			bulletLocation.Y += this->BulletSpawnRelativeLocation.Y;
		}
		ABullet* Bullet = this->GetWorld()->SpawnActor<ABullet>(this->BulletClass, bulletLocation, this->GetActorRotation());
		if (Bullet)
		{
			Bullet->FireSource = this;
			Bullet->FacingDirection = this->FacingDirection;
			Bullet->TravelSpeed = 15;
			Bullet->MaxTravelDistance = 5000;
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(23425, 10, FColor::Red, "ERR: Bullet class unset for gun: " + this->GetName());
	}
}

void AGun::Respawn() {
	this->SetActorLocation(this->InitialLocation);
}
