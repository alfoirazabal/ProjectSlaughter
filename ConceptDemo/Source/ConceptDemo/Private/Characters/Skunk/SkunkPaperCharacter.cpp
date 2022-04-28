// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skunk/SkunkPaperCharacter.h"

ASkunkPaperCharacter::ASkunkPaperCharacter()
{
	Super::SpecialPowerLoadTime = 2500;
}

void ASkunkPaperCharacter::Fire()
{
	if (IsValid(this->AttachedGun))
	{
		this->AttachedGun->Fire();
	}
	if (IsValid(this->AttachedGun))
	{
		this->CharacterHUD->SetStaminaBar(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}

void ASkunkPaperCharacter::UsePower()
{
	if (this->CurrentSpecialPowerLoadTime == this->SpecialPowerLoadTime)
	{
		if (this->SkunkFartCloud)
		{
			FVector SpawnLocation = this->GetActorLocation();
			SpawnLocation.X += 10;
			this->GetWorld()->SpawnActor<AFartCloud>(this->SkunkFartCloud, SpawnLocation, this->GetActorRotation());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(18572334, 2, FColor::Red, "Fart cloud not set for Skunk: " + this->GetName());
		}
		this->CurrentSpecialPowerLoadTime = 0;
	}
}
