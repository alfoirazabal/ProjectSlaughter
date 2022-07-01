// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Collectibles/LifeCollectible.h"

#include "Characters/ConceptDemoPaperCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ALifeCollectible::ALifeCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->LifeBarFill = 0.4;
	this->SpawnTime = 10;
	this->RotationSpeed = 3;

	UCapsuleComponent* TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(50.3, 59.1);
	TriggerCapsule->SetCollisionProfileName("Trigger");
	TriggerCapsule->SetupAttachment(this->RootComponent);

}

// Called when the game starts or when spawned
void ALifeCollectible::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALifeCollectible::SpawnTimeExpired, this->SpawnTime, false);
}

void ALifeCollectible::SpawnTimeExpired()
{
	this->Destroy();
}

// Called every frame
void ALifeCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator CurrentRotation = this->GetActorRotation();
	float CurrentRotationYaw = CurrentRotation.Yaw;
	CurrentRotationYaw += this->RotationSpeed;
	if (CurrentRotationYaw > 360) {
		CurrentRotationYaw = CurrentRotationYaw - 360;
	}
	CurrentRotation.Yaw = CurrentRotationYaw;
	this->SetActorRotation(CurrentRotation);
}
