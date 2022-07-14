// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Hedge/HedgeThorn.h"

#include "Characters/ConceptDemoPaperCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Characters/CharacterPowerProp.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpecialZones/DangerZone.h"
#include "Props/Platforms/SemiSolidPlatform.h"



// Sets default values
AHedgeThorn::AHedgeThorn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->DamageScore = 3.5;
	
	this->InitialPosition = this->GetActorLocation();
	this->TravelSpeed = 3;
	this->TotalDistanceTraveled = 0;
	this->MaxTravelDistance = 3000;
	this->ExplodingBulletClass = nullptr;
	this->ExplodingBullet = false;
	this->PythagoreanHickRelativeSize = 0;

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(35, 35);
	this->TriggerCapsule->SetCollisionProfileName("Trigger");
	this->TriggerCapsule->SetupAttachment(this->RootComponent);

	this->TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHedgeThorn::OnOverlapBegin);
	this->TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AHedgeThorn::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AHedgeThorn::BeginPlay()
{
	Super::BeginPlay();
	this->PythagoreanHick = this->TravelSpeed * this->PythagoreanHickRelativeSize;
    if (this->HedgeThornSource == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(298662235, 2, FColor::Red, "Programming error: Hedge Thorn source not set");
	}
	if (this->ShotSound)
	{
		this->ShotSoundComponent = UGameplayStatics::SpawnSound2D(this->GetWorld(), this->ShotSound);
		this->ShotSoundComponent->Play();
	}
}

// Called every frame
void AHedgeThorn::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentPosition = this->GetActorLocation();
	if (this->FacingDirection == EFacing_Direction::Right) {
		CurrentPosition.Y += this->TravelSpeed;
	}
	else if (this->FacingDirection == EFacing_Direction::Left) {
		CurrentPosition.Y -= this->TravelSpeed;
	}
	CurrentPosition.Z += this->PythagoreanHick;
	this->SetActorLocation(CurrentPosition);
	this->TotalDistanceTraveled += this->TravelSpeed;
	if (this->TotalDistanceTraveled >= this->MaxTravelDistance) {
		if (this->ShotSoundComponent) this->ShotSoundComponent->Stop();
		this->Destroy();
	}
}

void AHedgeThorn::DestroyOrExplodeBullet()
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
		this->GetWorld()->SpawnActor<AExplodingBullet>(this->ExplodingBulletClass, this->GetActorLocation(), Rotator);
	}
	if (this->ShotSoundComponent) this->ShotSoundComponent->Stop();
	this->Destroy();
}

void AHedgeThorn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp)
	{
		AConceptDemoPaperCharacter* Character = Cast<AConceptDemoPaperCharacter>(OtherActor);
		if (Character && Character != this->HedgeThornSource)
		{
			Character->Harm(this->HedgeThornDamage);
			const int EnemyDamageScore = this->HedgeThornDamage * 100;
			this->HedgeThornSource->OnEnemyDamaged.Broadcast(Character, this->HedgeThornSource, this, EnemyDamageScore);
			this->DestroyOrExplodeBullet();
		}
		else if (
			OtherActor != this && 
			!Cast<ADangerZone>(OtherActor) && 
			!Cast<AGun>(OtherActor) && 
			!Cast<ACharacterPowerProp>(OtherActor) &&
			!Cast<ASemiSolidPlatform>(OtherActor)
		)
		{
			this->DestroyOrExplodeBullet();
		}
	}
}

void AHedgeThorn::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex)
{
	
}

