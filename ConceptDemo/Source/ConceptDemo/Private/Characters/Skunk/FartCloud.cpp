// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skunk/FartCloud.h"

#include "Characters/ConceptDemoPaperCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFartCloud::AFartCloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->AliveTime = 25;
	this->AliveTimeLeft = this->AliveTime;
	this->InitialMovementSlowdownRatio = 0.12;
	this->FinalMovementSlowdownRatio = 0.25;
	this->MovementSlowdownDifference = this->FinalMovementSlowdownRatio - this->InitialMovementSlowdownRatio;
	this->CurrentMovementSlowdownRatio = this->InitialMovementSlowdownRatio;
	this->SkunkFartSource = nullptr;

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(155, 155);
	this->TriggerCapsule->SetCollisionProfileName("Trigger");
	this->TriggerCapsule->SetupAttachment(this->RootComponent);

	this->TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AFartCloud::OnOverlapBegin);
	this->TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AFartCloud::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AFartCloud::BeginPlay()
{
	Super::BeginPlay();
	if (this->SkunkFartSource == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(298662235, 2, FColor::Red, "Programming error: SKUNK Fart source not set");
	}
}

// Called every frame
void AFartCloud::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->AliveTimeLeft -= DeltaTime;
	if (AliveTimeLeft <= 0)
	{
		this->Destroy();
	}
	else
	{
		const float MovementSlowdownAffection = (this->AliveTimeLeft / this->AliveTime) * this->MovementSlowdownDifference;
		this->CurrentMovementSlowdownRatio = this->FinalMovementSlowdownRatio - MovementSlowdownAffection;
	}
}

int AFartCloud::FindCharacterWalkSpeedIndex(const AConceptDemoPaperCharacter* Character)
{
	int IndexFound = -1;
	for (int i = 0 ; IndexFound == -1 && i < this->OverlappingCharactersDefaultWalkSpeeds.Num() ; i++)
	{
		if (this->OverlappingCharactersDefaultWalkSpeeds[i].Character == Character)
		{
			IndexFound = i;
		}
	}
	return IndexFound;
}

void AFartCloud::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp)
	{
		AConceptDemoPaperCharacter* Character = Cast<AConceptDemoPaperCharacter>(OtherActor);
		if (Character)
		{
			if (this->SkunkFartSource != nullptr && Character != this->SkunkFartSource)
			{
				if (this->FindCharacterWalkSpeedIndex(Character) == -1)
				{
					FCharacterDefaultWalkSpeeds CharacterDefaultWalkSpeed;
					CharacterDefaultWalkSpeed.Character = Character;
					CharacterDefaultWalkSpeed.DefaultWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
					this->OverlappingCharactersDefaultWalkSpeeds.Add(CharacterDefaultWalkSpeed);
					Character->GetCharacterMovement()->MaxWalkSpeed *= this->CurrentMovementSlowdownRatio;
					Character->GetCharacterMovement()->SetJumpAllowed(false);
				}
			}
		}
	}
}

void AFartCloud::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherComp)
	{
		const AConceptDemoPaperCharacter* Character = Cast<AConceptDemoPaperCharacter>(OtherActor);
		if (Character)
		{
			if (this->SkunkFartSource != nullptr && Character != this->SkunkFartSource)
			{
				const int CharacterDefaultWalkSpeedIndex = this->FindCharacterWalkSpeedIndex(Character);
				if (CharacterDefaultWalkSpeedIndex != -1)
				{
					const FCharacterDefaultWalkSpeeds DefaultWalkSpeedFound = this->OverlappingCharactersDefaultWalkSpeeds[CharacterDefaultWalkSpeedIndex];
					Character->GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeedFound.DefaultWalkSpeed;
					this->OverlappingCharactersDefaultWalkSpeeds.RemoveAt(CharacterDefaultWalkSpeedIndex);
					Character->GetCharacterMovement()->SetJumpAllowed(true);
				}
			}
		}
	}
}

