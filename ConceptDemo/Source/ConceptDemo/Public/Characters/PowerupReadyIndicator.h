// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PowerupReadyIndicator.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API APowerupReadyIndicator : public APaperFlipbookActor
{
public:

	GENERATED_BODY()

	APowerupReadyIndicator();

	UPROPERTY() AActor* FollowingActor;
	UPROPERTY() FVector FollowingRelativePosition;

	virtual void Tick(float DeltaSeconds) override;
	
};
