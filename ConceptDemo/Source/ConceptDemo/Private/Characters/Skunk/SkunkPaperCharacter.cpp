// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skunk/SkunkPaperCharacter.h"

ASkunkPaperCharacter::ASkunkPaperCharacter()
{
	Super::SpecialPowerLoadTime = 2500;
	this->PlayerDescription = FString("SKUNK").Append(LINE_TERMINATOR).Append("Can throw toxic fart that slows down enemies");
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
			AFartCloud* FartCloud = this->GetWorld()->SpawnActor<AFartCloud>(this->SkunkFartCloud, SpawnLocation, this->GetActorRotation());
			FartCloud->SkunkFartSource = this;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(18572334, 2, FColor::Red, "Fart cloud not set for Skunk: " + this->GetName());
		}
		this->CurrentSpecialPowerLoadTime = 0;
	}
}

void ASkunkPaperCharacter::DropGun()
{
	Super::DropGun();
	this->UpdateHealthIndicator();
}

void ASkunkPaperCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->AttachedGun != nullptr && this->CurrentSpecialPowerLoadTime < this->SpecialPowerLoadTime)
	{
		this->CurrentSpecialPowerLoadTime++;
		this->UpdateHealthIndicator();
	}
}
