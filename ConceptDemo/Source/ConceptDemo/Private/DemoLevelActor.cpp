// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoLevelActor.h"

#include <Components/AudioComponent.h>

#include "DemoGameInstance.h"
#include "Kismet/GameplayStatics.h"

ADemoLevelActor::ADemoLevelActor()
{
	this->RandomPlayerSpawnLocations.Add(FVector(760, -650, 423));
	this->RandomPlayerSpawnLocations.Add(FVector(760, 370, 423));
	this->LevelGunsCount = 2;
	this->GunsSpawnCheckTimeInSeconds = 5;
	this->LifeCollectibleSpawnTimeInSeconds = 15;
	this->LifeCollectibleSpawnChance = 0.95;
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
	if (this->LifeCollectiblesSpawners.Num() > 0)
	{
		FTimerHandle TimerHandle;
		this->GetWorld()->GetTimerManager().SetTimer(
			TimerHandle, this, &ADemoLevelActor::SpawnCollectibles, this->LifeCollectibleSpawnTimeInSeconds, true
		);
	}
	if (this->LevelMusic.Num() > 0)
	{
		for (int i = 0 ; i < this->LevelMusic.Num() ; i++)
		{
			const int RandIndex = FMath::RandRange(0, this->LevelMusic.Num() - 1);
			this->LevelMusic.Swap(i, RandIndex);
		}
		this->CurrentBackgroundMusicPlayingIndex = 0;
		this->LevelMusicComponent = NewObject<UAudioComponent>(this->GetWorld());
		if (this->LevelMusicComponent)
		{
			this->LevelMusicComponent->SetSound(this->LevelMusic[0]);
			this->LevelMusicComponent->Play();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(28611252, 2, FColor::Red, "Level has no music! Can be changed in the editor");
	}
	if (this->BackgroundMusic)
	{
		UGameplayStatics::PlaySound2D(this->GetWorld(), this->BackgroundMusic);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(28611253, 5, FColor::Yellow, "Level has no background music! Can be changed in editor");
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
	this->InputComponent->BindAction(TEXT("P1 Use Power"), IE_Pressed, this, &ADemoLevelActor::P1UsePower);

	if (!this->GameInstance->UseControllerForPlayer2)
	{
		this->InputComponent->BindAxis(TEXT("P2 HorizontalMovement"), this, &ADemoLevelActor::P2HorizontalMovement);
		this->InputComponent->BindAction(TEXT("P2 Jump"), IE_Pressed, this, &ADemoLevelActor::P2JumpPressed);
		this->InputComponent->BindAction(TEXT("P2 Jump"), IE_Released, this, &ADemoLevelActor::P2JumpReleased);
		this->InputComponent->BindAction(TEXT("P2 Drop Down"), IE_Pressed, this, &ADemoLevelActor::P2DropDownPressed);
		this->InputComponent->BindAxis(TEXT("P2 Fire"), this, &ADemoLevelActor::P2Fire);
		this->InputComponent->BindAction(TEXT("P2 Drop Gun"), IE_Pressed, this, &ADemoLevelActor::P2DropGun);
		this->InputComponent->BindAction(TEXT("P2 Use Power"), IE_Pressed, this, &ADemoLevelActor::P2UsePower);
	}

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

void ADemoLevelActor::P1UsePower()
{
	if (IsValid(this->Player1)) this->Player1->UsePower();
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

void ADemoLevelActor::P2UsePower()
{
	if (IsValid(this->Player2)) this->Player2->UsePower();
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

	if (this->GameInstance->UseControllerForPlayer2)
	{
		this->Player2->SetPlayerNumber(EAutoReceiveInput::Player1);
		this->Player2->InputComponent = this->InputComponent;
		this->Player2->BindInputs();
	}
}


void ADemoLevelActor::SpawnGuns()
{
	int CurrentGunsInLevel = 0;
	for (int i = 0 ; i < this->SpawnerGuns.Num() ; i++)
	{
		const ASpawnerGun* SpawnerGun = this->SpawnerGuns[i];
		if (SpawnerGun->InUse) CurrentGunsInLevel++;
	}
	for (int i = CurrentGunsInLevel ; i < this->LevelGunsCount ; i++)
	{
		TArray<ASpawnerGun*> FreeSpawnSlots;
		for (int j = 0 ; j < this->SpawnerGuns.Num() ; j++)
		{
			ASpawnerGun* SpawnerGun = this->SpawnerGuns[j];
			if (!SpawnerGun->InUse) FreeSpawnSlots.Add(SpawnerGun);
		}
		if (FreeSpawnSlots.Num() > 0)
		{
			ASpawnerGun* RandomFreeSpawner = FreeSpawnSlots[FMath::RandRange(0, FreeSpawnSlots.Num() - 1)];
			TArray<TSubclassOf<AGun>> AvailableGuns;
			for (int j = 0 ; j < this->Guns.Num() ; j++)
			{
				if (RandomFreeSpawner->GunSpawnType.GetDefaultObject()->GunType == this->Guns[j].GetDefaultObject()->GunType)
				{
					AvailableGuns.Add(this->Guns[j]);
				}
			}
			if (AvailableGuns.Num() > 0)
			{
				TSubclassOf<AGun> RandomAvailableGun = AvailableGuns[FMath::RandRange(0, AvailableGuns.Num() - 1)];
				FRotator RandomGunRotation = this->GetActorRotation();
				RandomGunRotation.Yaw = FMath::RandRange(0, 360);
				AGun* Gun = this->GetWorld()->SpawnActor<AGun>(RandomAvailableGun, RandomFreeSpawner->GetActorLocation(), RandomGunRotation);
				RandomFreeSpawner->InUse = true;
				Gun->GunDead.AddDynamic(this, &ADemoLevelActor::ReactToGunDeath);
				CurrentGunsInLevel++;
				this->OnGunSpawned(Gun);
			}
		}
	}
}

void ADemoLevelActor::SpawnCollectibles()
{
	if (this->LifeCollectiblesType)
	{
		const float RandomSpawnChance = FMath::FRandRange(0, 1);
		if (RandomSpawnChance <= this->LifeCollectibleSpawnChance)
		{
			const uint16 RandomPosition = FMath::RandRange(0, this->LifeCollectiblesSpawners.Num() - 1);
			const AActor* RandomSpawnPosition = this->LifeCollectiblesSpawners[RandomPosition];
			this->GetWorld()->SpawnActor<ALifeCollectible>(
				this->LifeCollectiblesType, RandomSpawnPosition->GetActorLocation(), FRotator::ZeroRotator
			);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(129762361, 2, FColor::Red, "Can't spawn life collectible! Type not set on editor settings!");
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
