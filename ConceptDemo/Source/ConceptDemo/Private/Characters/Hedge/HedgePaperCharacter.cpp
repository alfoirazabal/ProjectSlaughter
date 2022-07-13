// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Hedge/HedgePaperCharacter.h"

#include <Kismet/GameplayStatics.h>


AHedgePaperCharacter::AHedgePaperCharacter()
{
	this->SpecialPowerLoadTime = 1000;
	this->ThornDamage = 0.25;
	this->ThornSpawnDistance = 75;
	this->RelativeGunAttachLocation = FVector(-5, -35, -45);

	this->PlayerDescription = FString("MEEDLE").Append(LINE_TERMINATOR).Append("Can throw thorns from his back and damage enemies");
}

void AHedgePaperCharacter::Fire()
{
	if (IsValid(this->AttachedGun))
	{
		this->AttachedGun->Fire(this);
	}
	if (IsValid(this->AttachedGun))
	{
		this->UserWidgetPlayersStatusControl->SetStaminaBar(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}

void AHedgePaperCharacter::UsePower()
{
    if (this->HedgeThornType != nullptr) {
        if (this->CurrentSpecialPowerLoadTime == this->SpecialPowerLoadTime)
        {
        	for (uint8 i = 0 ; i < 3 ; i++)
        	{
        		AHedgeThorn* HedgeThorn = this->GetWorld()->SpawnActorDeferred<AHedgeThorn>(this->HedgeThornType, FTransform::Identity, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
        		if (HedgeThorn)
        		{
        			float SpawnDistance = 0;
        			HedgeThorn->HedgeThornSource = this;
        			FRotator CurrentThornRotation = FRotator(0, 90, 0);
        			if (i == 0)
        			{
        				HedgeThorn->PythagoreanHickRelativeSize = 0.5;
        				CurrentThornRotation.Pitch = -25;
        			}
        			if (i == 2)
        			{
        				HedgeThorn->PythagoreanHickRelativeSize = -0.5;
        				CurrentThornRotation.Pitch = 25;
        			}
        			if (this->FacingDirection == EFacing_Direction::Left)
        			{
        				HedgeThorn->FacingDirection = EFacing_Direction::Right;
        				CurrentThornRotation.Yaw += 180;
        				SpawnDistance = this->ThornSpawnDistance;
        			}
        			if (this->FacingDirection == EFacing_Direction::Right)
        			{
        				HedgeThorn->FacingDirection = EFacing_Direction::Left;
        				SpawnDistance = -this->ThornSpawnDistance;
        			}
        			HedgeThorn->SetActorRotation(CurrentThornRotation);
        			HedgeThorn->TravelSpeed = 15;
        			HedgeThorn->HedgeThornDamage = this->ThornDamage;
        			FVector HedgeThornLocation = this->GetActorLocation();
        			HedgeThornLocation.Y += SpawnDistance;
        			HedgeThorn->SetActorLocation(HedgeThornLocation);
        			UGameplayStatics::FinishSpawningActor(HedgeThorn, FTransform::Identity);
        		}
        		else
        		{
        			GEngine->AddOnScreenDebugMessage(18572334, 2, FColor::Red, "Thorn not set for Hedge: " + this->GetName());
        		}
        	}
            Super::UsePower();
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
