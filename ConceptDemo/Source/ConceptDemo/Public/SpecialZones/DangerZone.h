// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConceptDemoPaperCharacter.h"
#include "Engine/StaticMeshActor.h"
#include "DangerZone.generated.h"

USTRUCT() struct FCharacterDefaultWalkSpeeds {
	GENERATED_BODY()
	UPROPERTY() AUConceptDemoPaperCharacter* Character;
	float DefaultWalkSpeed;
};

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API ADangerZone : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);

	TArray<FCharacterDefaultWalkSpeeds> OverlappingCharactersDefaultWalkSpeeds;
	UPROPERTY(EditAnywhere) float DamageHitDeltaSeconds;
	UPROPERTY(EditAnywhere) float ZoneDamage;
	UPROPERTY(EditAnywhere) float CharacterMovementSlowdownAmount;
	float CurrentDamageHitDeltaSeconds;
	
	virtual void Tick(float DeltaSeconds) override;

	int FindCharacterWalkSpeedIndex(const AUConceptDemoPaperCharacter* Character);
	
	ADangerZone();

	UPROPERTY(VisibleAnywhere, Category = "Trigger Box")
	class UBoxComponent* TriggerBox;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
