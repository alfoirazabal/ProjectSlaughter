// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialZones/DangerZone.h"

#include "ConceptDemoPaperCharacter.h"

ADangerZone::ADangerZone()
{
	this->ZoneDamage = 0.05;
	this->DamageHitDeltaSeconds = 50;
	this->CurrentDamageHitDeltaSeconds = this->DamageHitDeltaSeconds;
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
			AUConceptDemoPaperCharacter* Character = Cast<AUConceptDemoPaperCharacter>(OverlappingActor);
			if (Character)
			{
				Character->TakeDamage(this->ZoneDamage);
			}
		}
		this->CurrentDamageHitDeltaSeconds = this->DamageHitDeltaSeconds;
	}
}
