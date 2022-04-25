// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Rabbit/RabbitPaperCharacter.h"

ARabbitPaperCharacter::ARabbitPaperCharacter()
{
	this->SequentialJumps = 2;
	this->SequentialTimesJumped = 0;
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
