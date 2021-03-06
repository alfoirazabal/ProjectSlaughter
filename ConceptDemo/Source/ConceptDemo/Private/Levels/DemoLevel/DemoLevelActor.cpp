// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/DemoLevel/DemoLevelActor.h"

#include <Components/AudioComponent.h>

#include "DemoGameInstance.h"
#include "Internationalization/Culture.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/DemoLevel/DemoLevelGameModeBase.h"

ADemoLevelActor::ADemoLevelActor()
{
	this->RandomPlayerSpawnLocations.Add(FVector(760, -650, 423));
	this->RandomPlayerSpawnLocations.Add(FVector(760, 370, 423));
	this->LevelGunsCount = 2;
	this->GunsSpawnCheckTimeInSeconds = 5;
	this->LifeCollectibleSpawnTimeInSeconds = 15;
	this->LifeCollectibleSpawnChance = 0.95;
	static ConstructorHelpers::FClassFinder<UUserWidgetPlayersStatus> UserWidgetPLayerStatusClassFinder(TEXT("/Game/Widgets/PlayersScoreWidget"));
	this->UserWidgetPlayerStatusClass = UserWidgetPLayerStatusClassFinder.Class;
	static ConstructorHelpers::FClassFinder<UPlayersActionsWidget> PlayersActionsWidgetClassFinder(TEXT("/Game/Widgets/PlayersActionsWidget"));
	this->PlayersActionsWidgetClass = PlayersActionsWidgetClassFinder.Class;
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
	this->SetupPlayersStatusWidget();
	this->SetupInputs();
	this->Player1->PlayerDeath.AddDynamic(this, &ADemoLevelActor::P1ReactToDeath);
	this->Player2->PlayerDeath.AddDynamic(this, &ADemoLevelActor::P2ReactToDeath);
	this->Player1->PlayerLifeLost.AddDynamic(this, &ADemoLevelActor::P1ReactToLifeLost);
	this->Player2->PlayerLifeLost.AddDynamic(this, &ADemoLevelActor::P2ReactToLifeLost);
	this->Player1->PlayerGunAttached.AddDynamic(this, &ADemoLevelActor::P1UpdateGunStatus);
	this->Player1->PlayerGunDropped.AddDynamic(this, &ADemoLevelActor::P1UpdateGunStatus);
	this->Player2->PlayerGunAttached.AddDynamic(this, &ADemoLevelActor::P2UpdateGunStatus);
	this->Player2->PlayerGunDropped.AddDynamic(this, &ADemoLevelActor::P2UpdateGunStatus);
	this->Player1->PlayerPowerReady.AddDynamic(this, &ADemoLevelActor::ADemoLevelActor::P1UpdatePowerUpStatus);
	this->Player1->PlayerPowerUsed.AddDynamic(this, &ADemoLevelActor::ADemoLevelActor::P1UpdatePowerUpStatus);
	this->Player2->PlayerPowerReady.AddDynamic(this, &ADemoLevelActor::ADemoLevelActor::P2UpdatePowerUpStatus);
	this->Player2->PlayerPowerUsed.AddDynamic(this, &ADemoLevelActor::ADemoLevelActor::P2UpdatePowerUpStatus);
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
	this->Player1->OnEnemyDamaged.AddDynamic(this, &ADemoLevelActor::OnPlayerDamagedPlayer);
	this->Player2->OnEnemyDamaged.AddDynamic(this, &ADemoLevelActor::OnPlayerDamagedPlayer);
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

void ADemoLevelActor::SetupPlayersStatusWidget()
{
	ADemoLevelGameModeBase* GameModeBase = Cast<ADemoLevelGameModeBase>(UGameplayStatics::GetGameMode(this->GetWorld()));
	this->UserWidgetPlayersStatus = CreateWidget<UUserWidgetPlayersStatus>(this->GetWorld(), this->UserWidgetPlayerStatusClass);
	GameModeBase->PlayerStatusWidget = this->UserWidgetPlayersStatus;
	this->UserWidgetPlayersStatus->TxtP1Name->SetText(this->GameInstance->Player1Name);
	this->UserWidgetPlayersStatus->TxtP2Name->SetText(this->GameInstance->Player2Name);
	this->UserWidgetPlayersStatus->ImgP1CharacterType->SetBrushFromTexture(this->Player1->CharacterFaceImage);
	this->UserWidgetPlayersStatus->ImgP2CharacterType->SetBrushFromTexture(this->Player2->CharacterFaceImage);
	this->UserWidgetPlayersStatus->AddToViewport();
	this->PlayersActionsWidget = CreateWidget<UPlayersActionsWidget>(this->GetWorld(), this->PlayersActionsWidgetClass);
	this->PlayersActionsWidget->SetPlayerPowerUpTexture(1, this->Player1->PowerUpReadyIndicatorTexture);
	this->PlayersActionsWidget->SetPlayerPowerUpTexture(2, this->Player2->PowerUpReadyIndicatorTexture);
	this->PlayersActionsWidget->SetPlayerControllerType(1, EPlayersActionsWidgetControllerType::KeyboardPlayer1);
	if (this->GameInstance->UseControllerForPlayer2)
	{
		this->PlayersActionsWidget->SetPlayerControllerType(2, EPlayersActionsWidgetControllerType::XBoxController);
	}
	else
	{
		this->PlayersActionsWidget->SetPlayerControllerType(2, EPlayersActionsWidgetControllerType::KeyboardPlayer2);
	}
	this->PlayersActionsWidget->AddToViewport();
	UUserWidgetPlayersStatusControl* Player1StatusController = NewObject<UUserWidgetPlayersStatusControl>();
	UUserWidgetPlayersStatusControl* Player2StatusController = NewObject<UUserWidgetPlayersStatusControl>();
	Player1StatusController->ImgHeart1 = this->UserWidgetPlayersStatus->ImgP1Heart1;
	Player1StatusController->ImgHeart2 = this->UserWidgetPlayersStatus->ImgP1Heart2;
	Player1StatusController->ImgHeart3 = this->UserWidgetPlayersStatus->ImgP1Heart3;
	Player1StatusController->PbrHealth = this->UserWidgetPlayersStatus->PbrP1Life;
	Player1StatusController->PbrStamina = this->UserWidgetPlayersStatus->PbrP1Stamina;
	Player2StatusController->ImgHeart1 = this->UserWidgetPlayersStatus->ImgP2Heart1;
	Player2StatusController->ImgHeart2 = this->UserWidgetPlayersStatus->ImgP2Heart2;
	Player2StatusController->ImgHeart3 = this->UserWidgetPlayersStatus->ImgP2Heart3;
	Player2StatusController->PbrHealth = this->UserWidgetPlayersStatus->PbrP2Life;
	Player2StatusController->PbrStamina = this->UserWidgetPlayersStatus->PbrP2Stamina;
	this->Player1->UserWidgetPlayersStatusControl = Player1StatusController;
	this->Player2->UserWidgetPlayersStatusControl = Player2StatusController;
	this->Player1->UpdateHealthIndicator();
	this->Player2->UpdateHealthIndicator();
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
	this->Player1 = this->GetWorld()->SpawnActor<AConceptDemoPaperCharacter>(this->Player1Type, P1Location, PlayerSpawnRotation);
	this->Player2 = this->GetWorld()->SpawnActor<AConceptDemoPaperCharacter>(this->Player2Type, P2Location, PlayerSpawnRotation);

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

uint8 ADemoLevelActor::GetScoreWinnerPlayerNumber() const
{
	uint8 WinnerPlayerNumber;
	if (this->Player1->Score > this->Player2->Score)
	{
		WinnerPlayerNumber = 1;
	}
	else if (this->Player2->Score > this->Player1->Score)
	{
		WinnerPlayerNumber = 2;
	}
	else
	{
		WinnerPlayerNumber = 0;
	}
	return WinnerPlayerNumber;
}

void ADemoLevelActor::P1ReactToLifeLost()
{
	UGameplayStatics::SpawnSound2D(this->GetWorld(), this->Player2->PaperCharacterSounds.Kill);
}

void ADemoLevelActor::P2ReactToLifeLost()
{
	UGameplayStatics::SpawnSound2D(this->GetWorld(), this->Player1->PaperCharacterSounds.Kill);
}


void ADemoLevelActor::P1ReactToDeath()
{
	GEngine->AddOnScreenDebugMessage(35234211, 2, FColor::Yellow, "P1 Died");
	this->GameInstance->WinnerSurvivorPlayerNumber = 2;
	this->GameInstance->WinnerScorePlayerNumber = this->GetScoreWinnerPlayerNumber();
	this->GameInstance->Player1Score = this->Player1->Score;
	this->GameInstance->Player2Score = this->Player2->Score;
	UGameplayStatics::OpenLevel(this, "GameOverMenu");
}

void ADemoLevelActor::P2ReactToDeath()
{
	GEngine->AddOnScreenDebugMessage(35234212, 2, FColor::Yellow, "P2 Died");
	this->GameInstance->WinnerSurvivorPlayerNumber = 1;
	this->GameInstance->WinnerScorePlayerNumber = this->GetScoreWinnerPlayerNumber();
	this->GameInstance->Player1Score = this->Player1->Score;
	this->GameInstance->Player2Score = this->Player2->Score;
	UGameplayStatics::OpenLevel(this, "GameOverMenu");
}

void ADemoLevelActor::P1UpdateGunStatus()
{
	const bool GunActionsEnabled = this->Player1->HasGun();
	this->PlayersActionsWidget->UpdateHUD(1, DropGun, GunActionsEnabled);
	this->PlayersActionsWidget->UpdateHUD(1, FireGun, GunActionsEnabled);
}

void ADemoLevelActor::P2UpdateGunStatus()
{
	const bool GunActionsEnabled = this->Player2->HasGun();
	this->PlayersActionsWidget->UpdateHUD(2, DropGun, GunActionsEnabled);
	this->PlayersActionsWidget->UpdateHUD(2, FireGun, GunActionsEnabled);
}

void ADemoLevelActor::P1UpdatePowerUpStatus()
{
	const bool PowerUpEnabled = this->Player1->CanUsePower();
	this->PlayersActionsWidget->UpdateHUD(1, UsePower, PowerUpEnabled);
}

void ADemoLevelActor::P2UpdatePowerUpStatus()
{
	const bool PowerUpEnabled = this->Player2->CanUsePower();
	this->PlayersActionsWidget->UpdateHUD(2, UsePower, PowerUpEnabled);
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
	Gun->Sparkles->Destroy();
	Gun->Destroy();
}


void ADemoLevelActor::ExitLevel()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}

void ADemoLevelActor::OnPlayerDamagedPlayer(AActor* TargetedPawn, AActor* SourcePawn, AActor* Asset, const int DamageScore)
{
	AConceptDemoPaperPawn* ConceptDemoSourcePawn = Cast<AConceptDemoPaperPawn>(SourcePawn);
	const AConceptDemoPaperPawn* ConceptDemoTargetPawn = Cast<AConceptDemoPaperPawn>(TargetedPawn);
	if (ConceptDemoSourcePawn && ConceptDemoTargetPawn)
	{
		if (!ConceptDemoTargetPawn->Immune)
		{
			ConceptDemoSourcePawn->Score += DamageScore;
			UTextBlock* PlayerScoreText = nullptr;
			if (ConceptDemoSourcePawn == this->Player1)
			{
				PlayerScoreText = this->UserWidgetPlayersStatus->TxtP1Score;
			}
			else if (ConceptDemoSourcePawn == this->Player2)
			{
				PlayerScoreText = this->UserWidgetPlayersStatus->TxtP2Score;
			}
			PlayerScoreText->SetText(FText::AsNumber(ConceptDemoSourcePawn->Score));
		}
	}
}
