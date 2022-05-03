// Fill out your copyright notice in the Description page of Project Settings.


#include "SemiSolidPlatform.h"

#include "ConceptDemoPaperCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASemiSolidPlatform::ASemiSolidPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	this->TriggerBox->InitBoxExtent(FVector(1, 1, 1));
	this->TriggerBox->SetCollisionProfileName("Trigger");
	this->TriggerBox->SetupAttachment(this->RootComponent);

	this->TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASemiSolidPlatform::OnOverlapBegin);
	this->TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASemiSolidPlatform::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ASemiSolidPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASemiSolidPlatform::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASemiSolidPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp)
	{
		AUConceptDemoPaperCharacter* Character = Cast<AUConceptDemoPaperCharacter>(OtherActor);
		if (Character)
		{
			if (Character->GetCharacterMovement()->Velocity.Z > 0)
			{
				Character->MoveIgnoreActorAdd(this);
			}
			else
			{
				Character->MoveIgnoreActorRemove(this);
			}
		}
	}
}

void ASemiSolidPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}



