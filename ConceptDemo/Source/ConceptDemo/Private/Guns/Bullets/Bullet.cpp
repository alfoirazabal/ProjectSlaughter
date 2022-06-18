// Fill out your copyright notice in the Description page of Project Settings.


#include "Guns/Bullets/Bullet.h"

#include "Components/CapsuleComponent.h"
#include "Characters/ConceptDemoPaperCharacter.h"
#include "Characters/CharacterPowerProp.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Props/Collectibles/LifeCollectible.h"
#include "SpecialZones/DangerZone.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->InitialPosition = this->GetActorLocation();
	this->TravelSpeed = 3;
	this->TotalDistanceTraveled = 0;
	this->MaxTravelDistance = 5000;
	this->ExplodingBulletClass = nullptr;
	this->ExplodingBullet = false;

	this->BulletScoreMultiplier = 5;

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(13.45, 13.45);
	this->TriggerCapsule->SetCollisionProfileName("Trigger");
	this->TriggerCapsule->SetupAttachment(this->RootComponent);

	this->TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	this->TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	if (this->ShotSound)
	{
		this->ShotSoundComponent = UGameplayStatics::SpawnSound2D(this->GetWorld(), this->ShotSound);
		this->ShotSoundComponent->Play();
	}
}

// Called every frame
void ABullet::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentPosition = this->GetActorLocation();
	if (this->FacingDirection == EFacing_Direction::Right) {
		CurrentPosition.Y += this->TravelSpeed;
	}
	else if (this->FacingDirection == EFacing_Direction::Left) {
		CurrentPosition.Y -= this->TravelSpeed;
	}
	this->SetActorLocation(CurrentPosition);
	this->TotalDistanceTraveled += this->TravelSpeed;
	if (this->TotalDistanceTraveled >= this->MaxTravelDistance) {
		if (this->ShotSoundComponent) this->ShotSoundComponent->Stop();
		this->Destroy();
	}
}

void ABullet::DestroyOrExplodeBullet()
{
	if (!this->ExplodingBullet && this->ExplodingBulletClass != nullptr)
	{
		this->ExplodingBullet = true;
		FRotator Rotator = this->GetActorRotation();
		if (this->FacingDirection == Left)
		{
			Rotator.Roll = 180;
			Rotator.Pitch = 180;
		}
		AExplodingBullet* ExplodingBulletObject = this->GetWorld()->SpawnActorDeferred<AExplodingBullet>(
			this->ExplodingBulletClass, this->GetActorTransform(), this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
		ExplodingBulletObject->SourceActor = this->SourceActor;
		UGameplayStatics::FinishSpawningActor(ExplodingBulletObject, this->GetActorTransform());
		ExplodingBulletObject->SetActorRotation(Rotator);
	}
	if (this->ShotSoundComponent) this->ShotSoundComponent->Stop();
	this->Destroy();
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp)
	{
		AConceptDemoPaperCharacter* Character = Cast<AConceptDemoPaperCharacter>(OtherActor);
		if (Character)
		{
			if (
				(Character->AttachedGun != nullptr && this->SourceGun != nullptr && this->SourceActor != Character) ||
				Character->AttachedGun == nullptr
			) {
				this->TargetDamagedActor = Character;
				Character->TakeDamage(this->BulletDamage);
				const AConceptDemoPaperPawn* SourcePawn = Cast<AConceptDemoPaperPawn>(this->SourceActor);
				if (SourcePawn)
				{
					float DamageScore = this->BulletDamage *= this->BulletScoreMultiplier;
					SourcePawn->OnEnemyDamaged.Broadcast(Character, SourceActor, this, this->BulletDamage);
				}
				this->DestroyOrExplodeBullet();
			}
		}
		else if (OtherActor != this &&
			!Cast<ADangerZone>(OtherActor) &&
			!Cast<AGun>(OtherActor) &&
			!Cast<ACharacterPowerProp>(OtherActor) &&
			!Cast<ALifeCollectible>(OtherActor)
		)
		{
			this->DestroyOrExplodeBullet();
		}
	}
}

void ABullet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex)
{
	
}

