// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Droppables/Droppable.h"

// Sets default values
ADroppable::ADroppable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpawnTime = 1.5;
	this->RelativeSpriteSize = 0.4;
	
	this->PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	this->PaperSpriteComponent->SetupAttachment(this->RootComponent);
	this->PaperSpriteComponent->SetSimulatePhysics(true);
	this->PaperSpriteComponent->SetGenerateOverlapEvents(false);
	this->PaperSpriteComponent->SetCollisionProfileName("PhysicsActor");
    const float RelativeSize = this->RelativeSpriteSize;
	this->PaperSpriteComponent->SetRelativeScale3D(FVector(RelativeSize, RelativeSize, RelativeSize));
	
}

void ADroppable::Disappear()
{
	this->Destroy();
}

// Called when the game starts or when spawned
void ADroppable::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	this->GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, this, &ADroppable::Disappear, this->SpawnTime, false
	);
}

// Called every frame
void ADroppable::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

