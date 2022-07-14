// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialZones/DangerZone.h"

#include "Characters/ConceptDemoPaperCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADangerZone::ADangerZone()
{
	this->ZoneDamage = 0.05;
	this->DamageHitDeltaSeconds = 50;
	this->CurrentDamageHitDeltaSeconds = this->DamageHitDeltaSeconds;
	this->CharacterMovementSlowdownAmount = 0.5;

	this->TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	this->TriggerBox->InitBoxExtent(FVector(1, 1, 1));
	this->TriggerBox->SetCollisionProfileName("Trigger");
	this->TriggerBox->SetupAttachment(this->RootComponent);
	this->TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADangerZone::OnOverlapBegin);
	this->TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADangerZone::OnOverlapEnd);
	
	this->PrimaryActorTick.bCanEverTick = true;
}

void ADangerZone::Tick(float DeltaSeconds)
{
	this->CurrentDamageHitDeltaSeconds--;
	if (this->CurrentDamageHitDeltaSeconds == 0)
	{
		TArray<AActor*> OverlappingActors;
		this->GetOverlappingActors(OverlappingActors);
		for (AActor* OverlappingActor : OverlappingActors)
		{
			AConceptDemoPaperCharacter* Character = Cast<AConceptDemoPaperCharacter>(OverlappingActor);
			if (Character)
			{
				Character->Harm(this->ZoneDamage);
			}
		}
		this->CurrentDamageHitDeltaSeconds = this->DamageHitDeltaSeconds;
	}
}

int ADangerZone::FindCharacterWalkSpeedIndex(const AConceptDemoPaperCharacter* Character)
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

void ADangerZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp)
	{
		AConceptDemoPaperCharacter* Character = Cast<AConceptDemoPaperCharacter>(OtherActor);
		if (Character)
		{
			if (this->FindCharacterWalkSpeedIndex(Character) == -1)
			{
				FCharacterDefaultWalkSpeeds CharacterDefaultWalkSpeed;
				CharacterDefaultWalkSpeed.Character = Character;
				CharacterDefaultWalkSpeed.DefaultWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
				this->OverlappingCharactersDefaultWalkSpeeds.Add(CharacterDefaultWalkSpeed);
				Character->GetCharacterMovement()->MaxWalkSpeed *= this->CharacterMovementSlowdownAmount;
			}
		}
	}
}

void ADangerZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherComp)
	{
		const AConceptDemoPaperCharacter* Character = Cast<AConceptDemoPaperCharacter>(OtherActor);
		if (Character)
		{
			const int CharacterDefaultWalkSpeedIndex = this->FindCharacterWalkSpeedIndex(Character);
			if (CharacterDefaultWalkSpeedIndex != -1)
			{
				const FCharacterDefaultWalkSpeeds DefaultWalkSpeedFound = this->OverlappingCharactersDefaultWalkSpeeds[CharacterDefaultWalkSpeedIndex];
				Character->GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeedFound.DefaultWalkSpeed;
				this->OverlappingCharactersDefaultWalkSpeeds.RemoveAt(CharacterDefaultWalkSpeedIndex);
			}
		}
	}
}
