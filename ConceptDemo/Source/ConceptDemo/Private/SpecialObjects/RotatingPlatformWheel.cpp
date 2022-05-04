// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialObjects/RotatingPlatformWheel.h"

// Sets default values
ARotatingPlatformWheel::ARotatingPlatformWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->PlatformMovementSpeed = 5;
	this->PlatformsCount = 4;
	this->PlatformsWaitTime = 20;
	this->CurrentPlatformsDistanceTraveled = 0;
}

// Called when the game starts or when spawned
void ARotatingPlatformWheel::BeginPlay()
{
	Super::BeginPlay();
	this->CurrentPlatformsWaitTime = this->PlatformsWaitTime;
	this->PlatformWheelPath = Cast<USplineComponent>(this->GetComponentByClass(USplineComponent::StaticClass()));
	PrimaryActorTick.bCanEverTick = false;
	if (!IsValid(this->PlatformWheelPath))
	{
		GEngine->AddOnScreenDebugMessage(1998521, 2, FColor::Red, "Platform Wheel Path (Spline) not found");
	}
	else if (!IsValid(this->PlatformsType))
	{
		GEngine->AddOnScreenDebugMessage(19256621, 2, FColor::Red, "Need to define platform types for rotating wheel");
	}
	else
	{
		const float SplineLength = this->PlatformWheelPath->GetSplineLength();
		this->PlatformsDistanceBeforeWait = SplineLength / static_cast<float>(this->PlatformsCount);
		this->PlatformAndPaths.Reserve(this->PlatformsCount);
		for (uint8 i = 0 ; i < this->PlatformsCount ; i++)
		{
			const float CurrentPlatformSplineLength = (static_cast<float>(i) / static_cast<float>(this->PlatformsCount)) * SplineLength;
			FVector CurrentPlatformLocation = this->PlatformWheelPath->GetLocationAtDistanceAlongSpline(CurrentPlatformSplineLength, ESplineCoordinateSpace::World);
			FPlatformAndPath PlatformAndPath;
			PlatformAndPath.Platform = this->GetWorld()->SpawnActor<AActor>(this->PlatformsType, CurrentPlatformLocation, this->GetActorRotation());
			PlatformAndPath.PositionOnSpline = CurrentPlatformSplineLength;
			this->PlatformAndPaths.Add(PlatformAndPath);
		}
		this->PrimaryActorTick.bCanEverTick = true;
	}
}

void ARotatingPlatformWheel::MovePlatform(FPlatformAndPath& PlatformAndPath) const
{
	if (this->CurrentPlatformsDistanceTraveled + this->PlatformMovementSpeed > this->PlatformsDistanceBeforeWait)
	{
		PlatformAndPath.PositionOnSpline += (this->PlatformMovementSpeed + this->CurrentPlatformsDistanceTraveled) - this->PlatformsDistanceBeforeWait;
	}
	else
	{
		if (PlatformAndPath.PositionOnSpline + this->PlatformMovementSpeed > this->PlatformWheelPath->GetSplineLength())
		{
			PlatformAndPath.PositionOnSpline = this->PlatformMovementSpeed;
		}
		else
		{
			PlatformAndPath.PositionOnSpline += this->PlatformMovementSpeed;
		}
	}
	const FVector NewLocation = this->PlatformWheelPath->GetLocationAtDistanceAlongSpline(PlatformAndPath.PositionOnSpline, ESplineCoordinateSpace::World);
	PlatformAndPath.Platform->SetActorLocation(NewLocation);
}

// Called every frame
void ARotatingPlatformWheel::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->PlatformWheelPath)
	{
		if (this->CurrentPlatformsDistanceTraveled >= this->PlatformsDistanceBeforeWait)
		{
			this->CurrentPlatformsWaitTime--;
			if (this->CurrentPlatformsWaitTime == 0)
			{
				this->CurrentPlatformsWaitTime = this->PlatformsWaitTime;
				this->CurrentPlatformsDistanceTraveled = 0;
			}
		}
		else
		{
			for (uint8 i = 0 ; i < this->PlatformsCount ; i++)
			{
				this->MovePlatform(this->PlatformAndPaths[i]);
			}
			this->CurrentPlatformsDistanceTraveled += this->PlatformMovementSpeed;
		}
	}
}

