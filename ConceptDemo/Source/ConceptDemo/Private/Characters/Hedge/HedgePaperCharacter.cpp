// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Hedge/HedgePaperCharacter.h"

#include <Kismet/GameplayStatics.h>

AHedgePaperCharacter::AHedgePaperCharacter()
{
	Super::SpecialPowerLoadTime = 2500;
	this->ThornDamage = 0.035;

	this->PlayerDescription = FString("HEDGE").Append(LINE_TERMINATOR).Append("Can throw thorns from his back and damage enemies");
}

void AHedgePaperCharacter::Fire()
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

void AHedgePaperCharacter::UsePower()
{
    if (this->HedgeThorn != nullptr) {
        if (this->CurrentSpecialPowerLoadTime == this->SpecialPowerLoadTime)
        {
	        const FVector ThornLocation = this->GetActorLocation();
            
        }
    }
	else {
		GEngine->AddOnScreenDebugMessage(23425, 10, FColor::Red, "ERR: Thorn class unset for Hedge: " + this->GetName());
	}
}

void AHedgePaperCharacter::DropGun()
{
	Super::DropGun();
	this->UpdateHealthIndicator();
}

void AHedgePaperCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->AttachedGun != nullptr && this->CurrentSpecialPowerLoadTime < this->SpecialPowerLoadTime)
	{
		this->CurrentSpecialPowerLoadTime++;
		this->UpdateHealthIndicator();
	}
}
