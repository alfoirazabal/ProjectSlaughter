// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoLevelActor.h"

#include "Kismet/GameplayStatics.h"

void ADemoLevelActor::SetupInputs()
{
	this->InputComponent->BindAxis(TEXT("P1 HorizontalMovement"), this, &ADemoLevelActor::P1HorizontalMovement);
	this->InputComponent->BindAction(TEXT("P1 Jump"), IE_Pressed, this, &ADemoLevelActor::P1JumpPressed);
	this->InputComponent->BindAction(TEXT("P1 Jump"), IE_Released, this, &ADemoLevelActor::P1JumpReleased);
	this->InputComponent->BindAction(TEXT("P1 Drop Down"), IE_Pressed, this, &ADemoLevelActor::P1DropDownPressed);
	this->InputComponent->BindAction(TEXT("P1 Fire"), IE_Pressed, this, &ADemoLevelActor::P1Fire);
	this->InputComponent->BindAction(TEXT("P1 Drop Gun"), IE_Pressed, this, &ADemoLevelActor::P1DropGun);
	
	this->InputComponent->BindAxis(TEXT("P2 HorizontalMovement"), this, &ADemoLevelActor::P2HorizontalMovement);
	this->InputComponent->BindAction(TEXT("P2 Jump"), IE_Pressed, this, &ADemoLevelActor::P2JumpPressed);
	this->InputComponent->BindAction(TEXT("P2 Jump"), IE_Released, this, &ADemoLevelActor::P2JumpReleased);
	this->InputComponent->BindAction(TEXT("P2 Drop Down"), IE_Pressed, this, &ADemoLevelActor::P2DropDownPressed);
	this->InputComponent->BindAction(TEXT("P2 Fire"), IE_Pressed, this, &ADemoLevelActor::P2Fire);
	this->InputComponent->BindAction(TEXT("P2 Drop Gun"), IE_Pressed, this, &ADemoLevelActor::P2DropGun);

	this->InputComponent->BindAction(TEXT("Level Exit"), IE_Pressed, this, &ADemoLevelActor::ExitLevel);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(false);

	this->Player1->PlayerDeath.AddDynamic(this, &ADemoLevelActor::P1ReactToDeath);
	this->Player2->PlayerDeath.AddDynamic(this, &ADemoLevelActor::P2ReactToDeath);
}

void ADemoLevelActor::P1HorizontalMovement(const float AxisValue)
{
	if (IsValid(this->Player1)) this->Player1->HandleMovement(AxisValue);
}

void ADemoLevelActor::P1JumpPressed()
{
	if (IsValid(this->Player1)) this->Player1->Jump();
}

void ADemoLevelActor::P1JumpReleased()
{
	if (IsValid(this->Player1)) this->Player1->HandleStopJump();
}

void ADemoLevelActor::P1DropDownPressed()
{
	if (IsValid(this->Player1)) this->Player1->DropDown();
}

void ADemoLevelActor::P1Fire()
{
	if (IsValid(this->Player1)) this->Player1->Fire();
}

void ADemoLevelActor::P1DropGun()
{
	if (IsValid(this->Player1)) this->Player1->DropGun();
}

void ADemoLevelActor::P2HorizontalMovement(const float AxisValue)
{
	if (IsValid(this->Player2)) this->Player2->HandleMovement(AxisValue);
}

void ADemoLevelActor::P2JumpPressed()
{
	if (IsValid(this->Player2)) this->Player2->Jump();
}

void ADemoLevelActor::P2JumpReleased()
{
	if (IsValid(this->Player2)) this->Player2->HandleStopJump();
}

void ADemoLevelActor::P2DropDownPressed()
{
	if (IsValid(this->Player2)) this->Player2->DropDown();
}

void ADemoLevelActor::P2Fire()
{
	if (IsValid(this->Player2)) this->Player2->Fire();
}

void ADemoLevelActor::P2DropGun()
{
	if (IsValid(this->Player2)) this->Player2->DropGun();
}

void ADemoLevelActor::P1ReactToDeath()
{
	GEngine->AddOnScreenDebugMessage(35234211, 2, FColor::Yellow, "P1 Died");
}

void ADemoLevelActor::P2ReactToDeath()
{
	GEngine->AddOnScreenDebugMessage(35234212, 2, FColor::Yellow, "P2 Died");
}

void ADemoLevelActor::ExitLevel()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}
