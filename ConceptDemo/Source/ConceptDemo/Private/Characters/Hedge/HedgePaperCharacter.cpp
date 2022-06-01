// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Hedge/HedgePaperCharacter.h"

#include <Kismet/GameplayStatics.h>


AHedgePaperCharacter::AHedgePaperCharacter()
{
	this->SpecialPowerLoadTime = 0;
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
    if (this->HedgeThornType != nullptr) {
        if (this->CurrentSpecialPowerLoadTime == this->SpecialPowerLoadTime)
        {
        	for (uint8 i = 0 ; i < 3 ; i++)
        	{
        		AHedgeThorn* HedgeThorn = this->GetWorld()->SpawnActorDeferred<AHedgeThorn>(this->HedgeThornType, FTransform::Identity, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
        		HedgeThorn->SetActorLocation(this->GetActorLocation());
        		if (HedgeThorn)
        		{
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
        			}
        			if (this->FacingDirection == EFacing_Direction::Right)
        			{
        				HedgeThorn->FacingDirection = EFacing_Direction::Left;
        			}
        			HedgeThorn->SetActorRotation(CurrentThornRotation);
        			HedgeThorn->TravelSpeed = 15;
        			HedgeThorn->HedgeThornDamage = this->ThornDamage;
        			UGameplayStatics::FinishSpawningActor(HedgeThorn, FTransform::Identity);
        		}
        		else
        		{
        			GEngine->AddOnScreenDebugMessage(18572334, 2, FColor::Red, "Thorn not set for Hedge: " + this->GetName());
        		}
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
