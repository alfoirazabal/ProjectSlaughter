// Fill out your copyright notice in the Description page of Project Settings.


#include "Guns/Bullets/ExplodingBullet.h"

#include "Characters/ConceptDemoPaperCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AExplodingBullet::AExplodingBullet()
{
	this->DamageRadiusSize = 10;
	this->DamageDecreasesWithRadius = true;
	this->CurrentDamageRadiusSize = 1;
	this->InflationSpeed = 0.5;
	this->ExplosionDamage = 0.4;
	this->InitialDamage = this->ExplosionDamage;
	this->PrimaryActorTick.bCanEverTick = true;

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(54.5, 54.5);
	this->TriggerCapsule->SetCollisionProfileName("Trigger");
	this->TriggerCapsule->SetupAttachment(this->RootComponent);
}

void AExplodingBullet::BeginPlay()
{
	Super::BeginPlay();
	if (this->ExplosionSound)
	{
		UGameplayStatics::PlaySound2D(this->GetWorld(), this->ExplosionSound);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(28556112, 2, FColor::Yellow, "No Explosion Sound for ExplodingBullet: " + this->GetName());
	}
}

void AExplodingBullet::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	this->CurrentDamageRadiusSize += this->InflationSpeed;
	this->SetActorScale3D(FVector(this->CurrentDamageRadiusSize, this->CurrentDamageRadiusSize, this->CurrentDamageRadiusSize));
	if (this->DamageDecreasesWithRadius)
	{
		const float BulletDamageMultiplier = (this->DamageRadiusSize - this->CurrentDamageRadiusSize) / this->DamageRadiusSize;
		this->ExplosionDamage = this->InitialDamage * BulletDamageMultiplier;
	}
	if (this->CurrentDamageRadiusSize >= this->DamageRadiusSize)
	{
		this->Destroy();
	}
	TArray<AActor*> OverlappingActors;
	this->GetOverlappingActors(OverlappingActors);
	for (AActor* OverlappingActor : OverlappingActors)
	{
		AConceptDemoPaperCharacter* Character = Cast<AConceptDemoPaperCharacter>(OverlappingActor);
		if (Character)
		{
			if (!this->AffectedActors.Contains(Character))
			{
				Character->TakeDamage(this->ExplosionDamage);
				this->AffectedActors.Add(Character);
			}
		}
	}
}
