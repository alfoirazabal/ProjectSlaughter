// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Rabbit/RabbitPaperCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"

ARabbitPaperCharacter::ARabbitPaperCharacter()
{
	this->SequentialJumps = 2;
	this->SequentialTimesJumped = 0;
	Super::SpecialPowerLoadTime = 0;
	this->PlayerDescription = FString("RABBIT").Append(LINE_TERMINATOR).Append("Can double jump");
	this->SpecialPowerReadyPropShown = true;
}

void ARabbitPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->SpawnPowerUpReadyIndicator();
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
		this->AttachedGun->Fire(this);
	}
	if (IsValid(this->AttachedGun))
	{
		this->UserWidgetPlayersStatusControl->SetStaminaBar(this->AttachedGun->ShotsCount, this->AttachedGun->ShotsLeft);
	}
}

void ARabbitPaperCharacter::Landed(const FHitResult& Hit)
{
	this->SequentialTimesJumped = 0;
	this->SpawnPowerUpReadyIndicator();
	Super::Landed(Hit);
}

void ARabbitPaperCharacter::Jump()
{
	this->SequentialTimesJumped++;
	if (this->CurrentPowerUpReadyIndicator)
	{
		this->CurrentPowerUpReadyIndicator->Destroy();
	}
	if (this->SequentialTimesJumped == this->SequentialJumps)
	{
		UGameplayStatics::SpawnSound2D(this->GetWorld(), this->PaperCharacterSounds.SpecialSkill);
	}
	Super::Jump();
}

bool ARabbitPaperCharacter::CanJumpInternal_Implementation() const
{
	return this->SequentialTimesJumped <= this->SequentialJumps;
}

void ARabbitPaperCharacter::SpawnPowerUpReadyIndicator()
{
	if (this->CurrentPowerUpReadyIndicator)
	{
		this->CurrentPowerUpReadyIndicator->Destroy();
	}
	if (this->PowerUpReadyIndicatorType)
	{
		APowerupReadyIndicator* PowerUpReadyIndicator = this->GetWorld()->SpawnActor<APowerupReadyIndicator>(this->PowerUpReadyIndicatorType, this->GetActorLocation(), this->GetActorRotation());
		if (PowerUpReadyIndicator)
		{
			PowerUpReadyIndicator->FollowingActor = this;
			PowerUpReadyIndicator->FollowingRelativePosition = this->PowerUpReadyIndicatorRelativeLocation;
			PowerUpReadyIndicator->GetRenderComponent()->SetFlipbook(this->PowerUpReadyIndicatorFlipBook);
			this->CurrentPowerUpReadyIndicator = PowerUpReadyIndicator;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(192857125, 2, FColor::Red, "Failed to spawn Rabbit PowerUp Ready Indicator for: " + this->GetName());
		}
	}
}
