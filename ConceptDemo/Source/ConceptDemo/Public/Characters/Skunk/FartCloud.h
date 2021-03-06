// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ConceptDemoPaperCharacter.h"
#include "Characters/CharacterPowerProp.h"
#include "FartCloud.generated.h"

UCLASS()
class CONCEPTDEMO_API AFartCloud : public ACharacterPowerProp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFartCloud();

	UPROPERTY() AConceptDemoPaperCharacter* SkunkFartSource;
	UPROPERTY(EditAnywhere) float AliveTime;
	UPROPERTY() float AliveTimeLeft;
	UPROPERTY(EditAnywhere) float InitialMovementSlowdownRatio;
	UPROPERTY(EditAnywhere) float FinalMovementSlowdownRatio;
	UPROPERTY() float CurrentMovementSlowdownRatio;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY() float MovementSlowdownDifference;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);

	UPROPERTY() TArray<FCharacterDefaultWalkSpeeds> OverlappingCharactersDefaultWalkSpeeds;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int FindCharacterWalkSpeedIndex(const AConceptDemoPaperCharacter* Character);

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
