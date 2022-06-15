// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PowerupReadyIndicator.h"

#include "ConceptDemoPaperCharacter.h"

APowerupReadyIndicator::APowerupReadyIndicator()
{
	this->PrimaryActorTick.bCanEverTick = true;
}

void APowerupReadyIndicator::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (this->FollowingActor)
	{
		FVector NewLocation = this->FollowingActor->GetActorLocation();
		NewLocation += this->FollowingRelativePosition;
		this->SetActorLocation(NewLocation);
		const AUConceptDemoPaperCharacter* PaperCharacter = Cast<AUConceptDemoPaperCharacter>(this->FollowingActor);
		if (PaperCharacter)
		{
			const FRotator Rotation = PaperCharacter->GetFacingRotation();
			this->SetActorRotation(Rotation);
		}
		this->SetActorHiddenInGame(this->FollowingActor->IsHidden());
	}
}
