// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Rabbit/RabbitPaperCharacter.h"

ARabbitPaperCharacter::ARabbitPaperCharacter()
{
	this->SequentialJumps = 2;
	this->SequentialTimesJumped = 0;
	Super::SpecialPowerLoadTime = 0;
}

void ARabbitPaperCharacter::DropGun()
{
	Super::DropGun();
	Super::UpdateHealthIndicator();
}

void ARabbitPaperCharacter::Fire()
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

void ARabbitPaperCharacter::Landed(const FHitResult& Hit)
{
	this->SequentialTimesJumped = 0;
	Super::Landed(Hit);
}

void ARabbitPaperCharacter::Jump()
{
	this->SequentialTimesJumped++;
	Super::Jump();
}

bool ARabbitPaperCharacter::CanJumpInternal_Implementation() const
{
	return this->SequentialTimesJumped <= this->SequentialJumps;
}
