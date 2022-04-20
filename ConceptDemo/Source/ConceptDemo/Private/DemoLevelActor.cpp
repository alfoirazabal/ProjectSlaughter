// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoLevelActor.h"

#include "BlooPaperCharacter.h"
#include "DemoGameInstance.h"
#include "Kismet/GameplayStatics.h"

ADemoLevelActor::ADemoLevelActor()
{
	this->RandomPlayerSpawnLocations.Add(FVector(760, -650, 423));
	this->RandomPlayerSpawnLocations.Add(FVector(760, 370, 423));
	this->RandomGunSpawnLocations.Add(FVector(760, -340, 920));
	this->RandomGunSpawnLocations.Add(FVector(760, -60, 10));
	this->ReservedGunsSpawnLocations.Reserve(this->RandomGunSpawnLocations.Num());
	this->GunsSpawnCheckTimeInSeconds = 5;
	this->LevelGunsCount = this->RandomGunSpawnLocations.Num();
}


void ADemoLevelActor::BeginPlay()
{
	Super::BeginPlay();

	const UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(this->GetGameInstance());
	this->Player1Type = GameInstance->SelectedPlayer1Type;
	this->Player2Type = GameInstance->SelectedPlayer2Type;
	
	if (!this->Player1Type || !this->Player2Type)
	{
		GEngine->AddOnScreenDebugMessage(91652223, 2, FColor::Red, "Need to setup Demo Level characters on Player1 and Player2!");
	}
	else
	{
		this->SpawnPlayers();
		this->SetupInputs();
		this->Player1->PlayerDeath.AddDynamic(this, &ADemoLevelActor::P1ReactToDeath);
		this->Player2->PlayerDeath.AddDynamic(this, &ADemoLevelActor::P2ReactToDeath);
	}
	if (this->Guns.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(92576662, 2, FColor::Red, "Need to setup Demo Level guns!");
	}
	else
	{
		FTimerHandle TimerHandle;
		this->LevelGuns.Reserve(this->LevelGunsCount);
		this->GetWorld()->GetTimerManager().SetTimer(
			TimerHandle, this, &ADemoLevelActor::SpawnGuns, this->GunsSpawnCheckTimeInSeconds, true
		);
	}
}


void ADemoLevelActor::SetupInputs()
{
	this->InputComponent->BindAxis(TEXT("P1 HorizontalMovement"), this, &ADemoLevelActor::P1HorizontalMovement);
	this->InputComponent->BindAction(TEXT("P1 Jump"), IE_Pressed, this, &ADemoLevelActor::P1JumpPressed);
	this->InputComponent->BindAction(TEXT("P1 Jump"), IE_Released, this, &ADemoLevelActor::P1JumpReleased);
	this->InputComponent->BindAction(TEXT("P1 Drop Down"), IE_Pressed, this, &ADemoLevelActor::P1DropDownPressed);
	this->InputComponent->BindAxis(TEXT("P1 Fire"), this, &ADemoLevelActor::P1Fire);
	this->InputComponent->BindAction(TEXT("P1 Drop Gun"), IE_Pressed, this, &ADemoLevelActor::P1DropGun);
	
	this->InputComponent->BindAxis(TEXT("P2 HorizontalMovement"), this, &ADemoLevelActor::P2HorizontalMovement);
	this->InputComponent->BindAction(TEXT("P2 Jump"), IE_Pressed, this, &ADemoLevelActor::P2JumpPressed);
	this->InputComponent->BindAction(TEXT("P2 Jump"), IE_Released, this, &ADemoLevelActor::P2JumpReleased);
	this->InputComponent->BindAction(TEXT("P2 Drop Down"), IE_Pressed, this, &ADemoLevelActor::P2DropDownPressed);
	this->InputComponent->BindAxis(TEXT("P2 Fire"), this, &ADemoLevelActor::P2Fire);
	this->InputComponent->BindAction(TEXT("P2 Drop Gun"), IE_Pressed, this, &ADemoLevelActor::P2DropGun);

	this->InputComponent->BindAction(TEXT("Level Exit"), IE_Pressed, this, &ADemoLevelActor::ExitLevel);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(false);
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

void ADemoLevelActor::P1Fire(const float AxisValue)
{
	if (IsValid(this->Player1) && AxisValue == 1) this->Player1->Fire();
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

void ADemoLevelActor::P2Fire(const float AxisValue)
{
	if (IsValid(this->Player2) && AxisValue == 1) this->Player2->Fire();
}

void ADemoLevelActor::P2DropGun()
{
	if (IsValid(this->Player2)) this->Player2->DropGun();
}

void ADemoLevelActor::SpawnPlayers()
{
	const FRotator PlayerSpawnRotation = FRotator(0, 90, 0);
	const FVector P1Location = this->RandomPlayerSpawnLocations[FMath::RandRange(0, this->RandomPlayerSpawnLocations.Num() - 1)];
	this->RandomPlayerSpawnLocations.Remove(P1Location);
	const FVector P2Location = this->RandomPlayerSpawnLocations[FMath::RandRange(0, this->RandomPlayerSpawnLocations.Num() - 1)];
	this->RandomPlayerSpawnLocations.Remove(P2Location);
	this->Player1 = this->GetWorld()->SpawnActor<AUConceptDemoPaperCharacter>(this->Player1Type, P1Location, PlayerSpawnRotation);
	this->Player2 = this->GetWorld()->SpawnActor<AUConceptDemoPaperCharacter>(this->Player2Type, P2Location, PlayerSpawnRotation);
}


void ADemoLevelActor::SpawnGuns()
{
	bool NotEnoughSpawnLocations = false;
	while (!NotEnoughSpawnLocations && this->LevelGuns.Num() < this->LevelGunsCount)
	{
		FVector NewGunLocation = FVector::ZeroVector;
		for (int i = 0 ; this->RandomGunSpawnLocations.Num() > 0 && i < this->RandomGunSpawnLocations.Num() ; i++)
		{
			const int RandomIndex = FMath::RandRange(0, this->RandomGunSpawnLocations.Num() - 1);
			this->RandomGunSpawnLocations.Swap(i, RandomIndex);
		}
		for (int i = 0 ; NewGunLocation.Equals(FVector::ZeroVector) && i < this->LevelGunsCount ; i++)
		{
			if (i < this->RandomGunSpawnLocations.Num())
			{
				FVector CurrentRandomSpawnLocation = this->RandomGunSpawnLocations[i];
				if (!this->ReservedGunsSpawnLocations.Contains(CurrentRandomSpawnLocation))
				{
					NewGunLocation = CurrentRandomSpawnLocation;
					this->ReservedGunsSpawnLocations.Add(NewGunLocation);
				}
			}
		}
		if (NewGunLocation != FVector::ZeroVector)
		{
			AGun* NewGun = this->GetWorld()->SpawnActor<AGun>(this->Guns[FMath::RandRange(0, this->Guns.Num() - 1)], NewGunLocation, FRotator(0, FMath::RandRange(0, 360), 0));
			this->ReservedGunsSpawnLocations.Add(NewGunLocation);
			this->LevelGuns.Add(NewGun);
			NewGun->GunDead.AddDynamic(this, &ADemoLevelActor::ReactToGunDeath);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1985721, 2, FColor::Red, "Not enough gun spawn locations!");
			NotEnoughSpawnLocations = true;
		}
	}
}


void ADemoLevelActor::P1ReactToDeath()
{
	GEngine->AddOnScreenDebugMessage(35234211, 2, FColor::Yellow, "P1 Died");
}

void ADemoLevelActor::P2ReactToDeath()
{
	GEngine->AddOnScreenDebugMessage(35234212, 2, FColor::Yellow, "P2 Died");
}

void ADemoLevelActor::ReactToGunDeath(AGun* Gun)
{
	this->LevelGuns.Remove(Gun);
	this->ReservedGunsSpawnLocations.Remove(Gun->InitialLocation);
	if (this->Player1->AttachedGun == Gun) this->Player1->DropGun();
	if (this->Player2->AttachedGun == Gun) this->Player2->DropGun();
	Gun->Destroy();
}


void ADemoLevelActor::ExitLevel()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}
