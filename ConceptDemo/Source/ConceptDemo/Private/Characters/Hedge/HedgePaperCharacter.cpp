// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Hedge/HedgePaperCharacter.h"

#include <Kismet/GameplayStatics.h>

AHedgePaperCharacter::AHedgePaperCharacter()
{
	Super::SpecialPowerLoadTime = 2500;
	this->ThornDamage = 0.035;
	this->ThornSpawnRelativeLocation = FVector(0.0f, 50.0f, 10.0f);

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
	        FVector ThornLocation = this->GetActorLocation();
			ThornLocation.Z += this->ThornSpawnRelativeLocation.Z;
			if (this->FacingDirection == EFacing_Direction::Left) {
				ThornLocation.Y -= this->ThornSpawnRelativeLocation.Y;
			}
			else if (this->FacingDirection == EFacing_Direction::Right) {
				ThornLocation.Y += this->ThornSpawnRelativeLocation.Y;
			}
            AHedgeThorn* HedgeThorn = this->GetWorld()->SpawnActor<AHedgeThorn>(this->HedgeThorn, ThornLocation, this->GetActorRotation());
            if (HedgeThorn)
			{
				HedgeThorn->HedgeThornSource = this;
				HedgeThorn->FacingDirection = this->FacingDirection;
				HedgeThorn->TravelSpeed = 15;
				HedgeThorn->MaxTravelDistance = 5000;
				HedgeThorn->HedgeThornDamage = this->ThornDamage;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(18572334, 2, FColor::Red, "Thorn not set for Hedge: " + this->GetName());
			}
            UGameplayStatics::SpawnSound2D(this->GetWorld(), this->PowerSound);
            this->CurrentSpecialPowerLoadTime = 0;
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
