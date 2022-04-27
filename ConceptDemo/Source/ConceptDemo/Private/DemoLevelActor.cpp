// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoLevelActor.h"

#include "DemoGameInstance.h"
#include "Kismet/GameplayStatics.h"

ADemoLevelActor::ADemoLevelActor()
{
	this->RandomPlayerSpawnLocations.Add(FVector(760, -650, 423));
	this->RandomPlayerSpawnLocations.Add(FVector(760, 370, 423));
	this->LevelGunsCount = 2;
	this->GunsSpawnCheckTimeInSeconds = 5;
}


void ADemoLevelActor::BeginPlay()
{
	Super::BeginPlay();

	this->GameInstance = Cast<UDemoGameInstance>(this->GetGameInstance());
	if (IsValid(this->GameInstance))
	{
		UClass* Player1ClassType = this->GameInstance->SelectedPlayer1Type;
		UClass* Player2ClassType = this->GameInstance->SelectedPlayer2Type;
		if (IsValid(Player1ClassType)) this->Player1Type = Player1ClassType;
		if (IsValid(Player2ClassType)) this->Player2Type = Player2ClassType;
		if (!IsValid(Player1ClassType) || !IsValid(Player2ClassType))
		{
			GEngine->AddOnScreenDebugMessage(91652223, 4, FColor::Red, "Need to setup Demo Level characters for Player1 and Player2! Will spawn design set character");
		}
	}
	this->SpawnPlayers();
	this->SetupInputs();
	this->Player1->PlayerDeath.AddDynamic(this, &ADemoLevelActor::P1ReactToDeath);
	this->Player2->PlayerDeath.AddDynamic(this, &ADemoLevelActor::P2ReactToDeath);
	if (this->Guns.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(92576662, 2, FColor::Red, "Need to setup Demo Level guns!");
	}
	else
	{
		if (this->LevelGunsCount > this->SpawnerGuns.Num())
		{
			GEngine->AddOnScreenDebugMessage(190275272, 2, FColor::Red, "Not enough SpawnerGuns for Level Guns Count");
		}
		else
		{
			FTimerHandle TimerHandle;
			this->GetWorld()->GetTimerManager().SetTimer(
				TimerHandle, this, &ADemoLevelActor::SpawnGuns, this->GunsSpawnCheckTimeInSeconds, true
			);
		}
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
	if (IsValid(this->Player1)) this->Player1->StopJumping();
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
	if (IsValid(this->Player2)) this->Player2->StopJumping();
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
	this->Player1->SetPlayerName(this->GameInstance->Player1Name);
	this->Player2->SetPlayerName(this->GameInstance->Player2Name);
}


void ADemoLevelActor::SpawnGuns()
{
	int GunsSpawned = 0;
	for (int i = 0 ; i < this->SpawnerGuns.Num() ; i++)
	{
		const int RandomIndex = FMath::RandRange(0, this->SpawnerGuns.Num() - 1);
		this->SpawnerGuns.Swap(i, RandomIndex);
	}
	TArray<ASpawnerGun*> CurrentFreeSpawners;
	for (ASpawnerGun* SpawnerGun : this->SpawnerGuns)
	{
		if (!SpawnerGun->InUse)
		{
			CurrentFreeSpawners.Add(SpawnerGun);
		}
		else
		{
			GunsSpawned++;
		}
	}
	for (ASpawnerGun* SpawnerGun : CurrentFreeSpawners)
	{
		TArray<TSubclassOf<AGun>> AvailableGunsOfSpawnType;
		for (TSubclassOf<AGun> AvailableGunClass : this->Guns)
		{
			if (AvailableGunClass.GetDefaultObject()->SpawnChance == SpawnerGun->GunSpawnRarity)
			{
				AvailableGunsOfSpawnType.Add(AvailableGunClass);
			}
		}
		if (AvailableGunsOfSpawnType.Num() > 0)
		{
			TSubclassOf<AGun> GunClassToSpawn = AvailableGunsOfSpawnType[FMath::RandRange(0, AvailableGunsOfSpawnType.Num() - 1)];
			if (GunsSpawned <= this->LevelGunsCount)
			{
				FRotator RandomRotation = FRotator(0, FMath::RandRange(0, 360), 0);
				AGun* NewGun = this->GetWorld()->SpawnActor<AGun>(GunClassToSpawn, SpawnerGun->GetActorLocation(), RandomRotation);
				SpawnerGun->InUse = true;
				NewGun->GunDead.AddDynamic(this, &ADemoLevelActor::ReactToGunDeath);
				GunsSpawned++;
			}
		}
	}
}


void ADemoLevelActor::P1ReactToDeath()
{
	GEngine->AddOnScreenDebugMessage(35234211, 2, FColor::Yellow, "P1 Died");
	this->GameInstance->WinningPlayerNumber = 2;
	UGameplayStatics::OpenLevel(this, "GameOverMenu");
}

void ADemoLevelActor::P2ReactToDeath()
{
	GEngine->AddOnScreenDebugMessage(35234212, 2, FColor::Yellow, "P2 Died");
	this->GameInstance->WinningPlayerNumber = 1;
	UGameplayStatics::OpenLevel(this, "GameOverMenu");
}

void ADemoLevelActor::ReactToGunDeath(AGun* Gun)
{
	ASpawnerGun* SpawnerGunFound = nullptr;
	for (int i = 0 ; SpawnerGunFound == nullptr && i < this->SpawnerGuns.Num() ; i++)
	{
		if (this->SpawnerGuns[i]->GetActorLocation() == Gun->InitialLocation)
		{
			SpawnerGunFound = this->SpawnerGuns[i];
		}
	}
	if (SpawnerGunFound)
	{
		SpawnerGunFound->InUse = false;
	}
	if (this->Player1->AttachedGun == Gun) this->Player1->DropGun();
	if (this->Player2->AttachedGun == Gun) this->Player2->DropGun();
	Gun->Destroy();
}


void ADemoLevelActor::ExitLevel()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}
