// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/PlayerSelectionWidget.h"

#include "DemoGameInstance.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

UPlayerSelectionWidget::UPlayerSelectionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AConceptDemoPaperCharacter> RabbitYellowClassFinder(TEXT("/Game/Character/Rabbit/Yellow/YellowRabbitCharacter"));
	static ConstructorHelpers::FClassFinder<AConceptDemoPaperCharacter> RabbitVioletClassFinder(TEXT("/Game/Character/Rabbit/Violet/VioletRabbitCharacter"));
	static ConstructorHelpers::FClassFinder<AConceptDemoPaperCharacter> SkunkClassFinder(TEXT("/Game/Character/Skunk/SkunkCharacter"));
	static ConstructorHelpers::FClassFinder<AConceptDemoPaperCharacter> SkunkAltClassFinder(TEXT("/Game/Character/SkunkAlt/SkunkAltCharacter"));
	static ConstructorHelpers::FClassFinder<AConceptDemoPaperCharacter> HedgeRedClassFinder(TEXT("/Game/Character/Hedge/Red/HedgeRedCharacter"));
	static ConstructorHelpers::FClassFinder<AConceptDemoPaperCharacter> HedgeBlueClassFinder(TEXT("/Game/Character/Hedge/Blue/HedgeBlueCharacter"));
	const TSubclassOf<AConceptDemoPaperCharacter> RabbitYellowClass = RabbitYellowClassFinder.Class;
	const TSubclassOf<AConceptDemoPaperCharacter> RabbitVioletClass = RabbitVioletClassFinder.Class;
	const TSubclassOf<AConceptDemoPaperCharacter> SkunkClass = SkunkClassFinder.Class;
	const TSubclassOf<AConceptDemoPaperCharacter> SkunkAltClass = SkunkAltClassFinder.Class;
	const TSubclassOf<AConceptDemoPaperCharacter> HedgeRedClass = HedgeRedClassFinder.Class;
	const TSubclassOf<AConceptDemoPaperCharacter> HedgeBlueClass = HedgeBlueClassFinder.Class;
	this->CharacterTypes.Add(RabbitYellowClass);
	this->CharacterTypes.Add(SkunkClass);
	this->CharacterTypes.Add(HedgeRedClass);
	this->CharacterTypes.Add(RabbitVioletClass);
	this->CharacterTypes.Add(SkunkAltClass);
	this->CharacterTypes.Add(HedgeBlueClass);
	for (uint16 i = 0 ; i < this->CharacterTypes.Num() ; i++)
	{
		AConceptDemoPaperCharacter* CharacterP1 = Cast<AConceptDemoPaperCharacter>(this->CharacterTypes[i]->GetDefaultObject());
		AConceptDemoPaperCharacter* CharacterP2 = Cast<AConceptDemoPaperCharacter>(this->CharacterTypes[i]->GetDefaultObject());
		this->P1Characters.Add(CharacterP1);
		this->P2Characters.Add(CharacterP2);
	}
}

void UPlayerSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	this->BackgroundTextureSequenceFlipTime = 0.2;
	this->GetWorld()->GetTimerManager().SetTimer(
		this->BackgroundImageFlippingTimer, this, &UPlayerSelectionWidget::SetBackgroundImageFlipping,
		this->BackgroundTextureSequenceFlipTime, true
	);
	this->P1CharacterImages.Add(this->ImgP1Pos1);
	this->P1CharacterImages.Add(this->ImgP1Pos2);
	this->P1CharacterImages.Add(this->ImgP1Pos3);
	this->P1CharacterImages.Add(this->ImgP1Pos4);
	this->P1CharacterImages.Add(this->ImgP1Pos5);
	this->P1CharacterImages.Add(this->ImgP1Pos6);
	this->P2CharacterImages.Add(this->ImgP2Pos1);
	this->P2CharacterImages.Add(this->ImgP2Pos2);
	this->P2CharacterImages.Add(this->ImgP2Pos3);
	this->P2CharacterImages.Add(this->ImgP2Pos4);
	this->P2CharacterImages.Add(this->ImgP2Pos5);
	this->P2CharacterImages.Add(this->ImgP2Pos6);
	this->P1SelectionMarkerImages.Add(this->ImgSelectedP1Pos1);
	this->P1SelectionMarkerImages.Add(this->ImgSelectedP1Pos2);
	this->P1SelectionMarkerImages.Add(this->ImgSelectedP1Pos3);
	this->P1SelectionMarkerImages.Add(this->ImgSelectedP1Pos4);
	this->P1SelectionMarkerImages.Add(this->ImgSelectedP1Pos5);
	this->P1SelectionMarkerImages.Add(this->ImgSelectedP1Pos6);
	this->P2SelectionMarkerImages.Add(this->ImgSelectedP2Pos1);
	this->P2SelectionMarkerImages.Add(this->ImgSelectedP2Pos2);
	this->P2SelectionMarkerImages.Add(this->ImgSelectedP2Pos3);
	this->P2SelectionMarkerImages.Add(this->ImgSelectedP2Pos4);
	this->P2SelectionMarkerImages.Add(this->ImgSelectedP2Pos5);
	this->P2SelectionMarkerImages.Add(this->ImgSelectedP2Pos6);
	for (uint8 i = 0 ; i < 6 ; i++)
	{
		this->P1CharacterImages[i]->SetBrushFromTexture(this->P1Characters[i]->CharacterFaceImage);
		this->P2CharacterImages[i]->SetBrushFromTexture(this->P2Characters[i]->CharacterFaceImage);
	}
	this->Player1Character = this->P1Characters[FMath::RandRange(0, this->P1Characters.Num() - 1)];
	this->Player2Character = this->P2Characters[FMath::RandRange(0, this->P2Characters.Num() - 1)];
	this->DisplaySelectedP1();
	this->DisplaySelectedP2();
	this->ButtonBegin->OnClicked.AddDynamic(this, &UPlayerSelectionWidget::BeginGame);
	const APlayerController* PlayerController = this->GetOwningPlayer();
	PlayerController->InputComponent->BindAction(TEXT("P1 Left"), IE_Pressed, this, &UPlayerSelectionWidget::P1SelectLeftwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("P1 Up"), IE_Pressed, this, &UPlayerSelectionWidget::P1SelectUpwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("P1 Right"), IE_Pressed, this, &UPlayerSelectionWidget::P1SelectRightwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("P1 Down"), IE_Pressed, this, &UPlayerSelectionWidget::P1SelectDownwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("P2 Left"), IE_Pressed, this, &UPlayerSelectionWidget::P2SelectLeftwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("P2 Up"), IE_Pressed, this, &UPlayerSelectionWidget::P2SelectUpwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("P2 Right"), IE_Pressed, this, &UPlayerSelectionWidget::P2SelectRightwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("P2 Down"), IE_Pressed, this, &UPlayerSelectionWidget::P2SelectDownwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("C Up"), IE_Pressed, this, &UPlayerSelectionWidget::P2SelectUpwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("C Down"), IE_Pressed, this, &UPlayerSelectionWidget::P2SelectDownwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("C Right"), IE_Pressed, this, &UPlayerSelectionWidget::P2SelectRightwardsPlayer);
	PlayerController->InputComponent->BindAction(TEXT("C Left"), IE_Pressed, this, &UPlayerSelectionWidget::P2SelectLeftwardsPlayer);
}

void UPlayerSelectionWidget::NativeDestruct()
{
	this->GetWorld()->GetTimerManager().ClearTimer(this->BackgroundImageFlippingTimer);
	Super::NativeDestruct();
}

void UPlayerSelectionWidget::GoBack()
{
	GEngine->AddOnScreenDebugMessage(287572113, 2, FColor::Green, "Implemented on Blueprints");
}

void UPlayerSelectionWidget::BeginGame()
{
	UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(this->GetGameInstance());
	UClass* Player1CharacterClass = this->Player1Character->GetClass();
	UClass* Player2CharacterClass = this->Player2Character->GetClass();
	if (IsValid(Player1CharacterClass)) GameInstance->SelectedPlayer1Type = Player1CharacterClass;
	if (IsValid(Player2CharacterClass)) GameInstance->SelectedPlayer2Type = Player2CharacterClass;
	GameInstance->Player1Name = this->EditableTextBoxPlayer1Name->Text;
	GameInstance->Player2Name = this->EditableTextBoxPlayer2Name->Text;
	UGameplayStatics::OpenLevel(this, "/Game/DemoLevel");
}

void UPlayerSelectionWidget::SetBackgroundImageFlipping()
{
	if (this->BackgroundTextureSequence.Num() > 0)
	{
		this->CurrentFlippingImageIndex++;
		if (this->CurrentFlippingImageIndex > this->BackgroundTextureSequence.Num() - 1)
		{
			this->CurrentFlippingImageIndex = 0;
		}
		this->BackgroundImage->SetBrushFromTexture(this->BackgroundTextureSequence[this->CurrentFlippingImageIndex]);
	}
}

void UPlayerSelectionWidget::P1SelectLeftwardsPlayer()
{
	const int CurrentIndex = this->P1Characters.IndexOfByKey(this->Player1Character);
	if (CurrentIndex != 0 && CurrentIndex != 3)
	{
		const int LeftwardsIndex = CurrentIndex - 1;
		this->Player1Character = this->P1Characters[LeftwardsIndex];
		this->DisplaySelectedP1();
	}
}
void UPlayerSelectionWidget::P1SelectUpwardsPlayer()
{
	const int CurrentIndex = this->P1Characters.IndexOfByKey(this->Player1Character);
	if (CurrentIndex > 2)
	{
		const int UpwardsIndex = CurrentIndex - 3;
		this->Player1Character = this->P1Characters[UpwardsIndex];
		this->DisplaySelectedP1();
	}
}
void UPlayerSelectionWidget::P1SelectRightwardsPlayer()
{
	const int CurrentIndex = this->P1Characters.IndexOfByKey(this->Player1Character);
	if (CurrentIndex != 2 && CurrentIndex != 5)
	{
		const int RightwardsIndex = CurrentIndex + 1;
		this->Player1Character = this->P1Characters[RightwardsIndex];
		this->DisplaySelectedP1();
	}
}
void UPlayerSelectionWidget::P1SelectDownwardsPlayer()
{
	const int CurrentIndex = this->P1Characters.IndexOfByKey(this->Player1Character);
	if (CurrentIndex < 3)
	{
		const int DownwardsIndex = CurrentIndex + 3;
		this->Player1Character = this->P1Characters[DownwardsIndex];
		this->DisplaySelectedP1();
	}
}

void UPlayerSelectionWidget::P2SelectLeftwardsPlayer()
{
	const int CurrentIndex = this->P2Characters.IndexOfByKey(this->Player2Character);
	if (CurrentIndex != 0 && CurrentIndex != 3)
	{
		const int LeftwardsIndex = CurrentIndex - 1;
		this->Player2Character = this->P2Characters[LeftwardsIndex];
		this->DisplaySelectedP2();
	}
}
void UPlayerSelectionWidget::P2SelectUpwardsPlayer()
{
	const int CurrentIndex = this->P2Characters.IndexOfByKey(this->Player2Character);
	if (CurrentIndex > 2)
	{
		const int UpwardsIndex = CurrentIndex - 3;
		this->Player2Character = this->P2Characters[UpwardsIndex];
		this->DisplaySelectedP2();
	}
}
void UPlayerSelectionWidget::P2SelectRightwardsPlayer()
{
	const int CurrentIndex = this->P2Characters.IndexOfByKey(this->Player2Character);
	if (CurrentIndex != 2 && CurrentIndex != 5)
	{
		const int RightwardsIndex = CurrentIndex + 1;
		this->Player2Character = this->P2Characters[RightwardsIndex];
		this->DisplaySelectedP2();
	}
}
void UPlayerSelectionWidget::P2SelectDownwardsPlayer()
{
	const int CurrentIndex = this->P2Characters.IndexOfByKey(this->Player2Character);
	if (CurrentIndex < 3)
	{
		const int DownwardsIndex = CurrentIndex + 3;
		this->Player2Character = this->P2Characters[DownwardsIndex];
		this->DisplaySelectedP2();
	}
}

void UPlayerSelectionWidget::DisplaySelectedP1()
{
	const uint8 SelectedCharacterIndex = this->P1Characters.IndexOfByKey(this->Player1Character);
	for (uint8 i = 0 ; i < this->P1CharacterImages.Num() ; i++)
	{
		if (i == SelectedCharacterIndex)
		{
			this->P1SelectionMarkerImages[i]->SetVisibility(ESlateVisibility::Visible);
			this->RichTextBlockPlayer1Description->SetText(FText::FromString(this->Player1Character->PlayerDescription));
		}
		else
		{
			this->P1SelectionMarkerImages[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	this->ImgP1Body->SetBrushFromTexture(this->Player1Character->CharacterImage);
}

void UPlayerSelectionWidget::DisplaySelectedP2()
{
	const uint8 SelectedCharacterIndex = this->P2Characters.IndexOfByKey(this->Player2Character);
	for (uint8 i = 0 ; i < this->P2CharacterImages.Num() ; i++)
	{
		if (i == SelectedCharacterIndex)
		{
			this->P2SelectionMarkerImages[i]->SetVisibility(ESlateVisibility::Visible);
			this->RichTextBlockPlayer2Description->SetText(FText::FromString(this->Player2Character->PlayerDescription));
		}
		else
		{
			this->P2SelectionMarkerImages[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	this->ImgP2Body->SetBrushFromTexture(this->Player2Character->CharacterImage);
}
