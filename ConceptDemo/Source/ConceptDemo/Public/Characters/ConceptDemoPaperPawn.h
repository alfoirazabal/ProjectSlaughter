// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SlaughterFriendsDemoConstants.h"
#include "ConceptDemoPaperPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnEnemyDamaged, AActor*, TargetPawn, AActor*, SourcePawn, AActor*, Asset, int, DamageScore);

UCLASS()
class CONCEPTDEMO_API AConceptDemoPaperPawn : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AConceptDemoPaperPawn();

	UPROPERTY() bool Frozen;
	UPROPERTY() bool Immune;
	UPROPERTY() bool bFallingDeath;

	UFUNCTION() void EnsureXAxisLocation();
	UFUNCTION() bool IsOnTheAir() const;
	
	UFUNCTION() static FRotator GetRightRotator();
	UFUNCTION() static FRotator GetLeftRotator();

	UPROPERTY() int Score;
	UPROPERTY() FOnEnemyDamaged OnEnemyDamaged;
	
	UPROPERTY() FVector InitialPosition;
	UPROPERTY() TEnumAsByte<EFacing_Direction> FacingDirection;
	
	UFUNCTION() FRotator GetFacingRotation() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPlayerNumber(TEnumAsByte<EAutoReceiveInput::Type> PlayerNumber);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};