// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Collectibles/LifeCollectible.h"

#include "ConceptDemoPaperCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ALifeCollectible::ALifeCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->LifeBarFill = 0.4;
	this->SpawnTime = 10;

	this->TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	this->TriggerCapsule->InitCapsuleSize(50.3, 59.1);
	this->TriggerCapsule->SetCollisionProfileName("Trigger");
	this->TriggerCapsule->SetupAttachment(this->RootComponent);

}

// Called when the game starts or when spawned
void ALifeCollectible::BeginPlay()
{
	Super::BeginPlay();

	this->TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ALifeCollectible::OnOverlapBegin);

	FTimerHandle TimerHandle;
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALifeCollectible::SpawnTimeExpired, this->SpawnTime, false);
}

void ALifeCollectible::SpawnTimeExpired()
{
	this->Destroy();
}

// Called every frame
void ALifeCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALifeCollectible::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(235236236, 2, FColor::Green, "COL0");
	if (OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(235236236, 2, FColor::Green, "COL1");
		if (OtherActor)
		{
			GEngine->AddOnScreenDebugMessage(235236236, 2, FColor::Green, "COL2");
			AUConceptDemoPaperCharacter* Character = Cast<AUConceptDemoPaperCharacter>(OtherActor);
			if (Character)
			{
				GEngine->AddOnScreenDebugMessage(235236236, 2, FColor::Green, "COL3");
				Character->AddLife(this->LifeBarFill);
				this->Destroy();
			}
		}
	}
}

