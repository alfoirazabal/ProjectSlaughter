// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenuGameModeBase.h"

#include "Components/AudioComponent.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	this->BackgroundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Background Audio Component"));
	this->ReplayIfSameAudioIsRequested = false;
}

void AMainMenuGameModeBase::PlayBackgroundAudio(USoundBase* Sound) const
{
	if (this->ReplayIfSameAudioIsRequested)
	{
		this->StopBackgroundAudio();
		this->BackgroundAudioComponent->SetSound(Sound);
		this->BackgroundAudioComponent->Play();
	}
	else
	{
		if (this->BackgroundAudioComponent->Sound)
		{
			const FString CurrentBackgroundSoundName = this->BackgroundAudioComponent->Sound->GetName();
			const FString NewSoundName = Sound->GetName();
			if (!CurrentBackgroundSoundName.Equals(NewSoundName))
			{
				this->StopBackgroundAudio();
				this->BackgroundAudioComponent->SetSound(Sound);
				this->BackgroundAudioComponent->Play();
			}
		}
		else
		{
			this->BackgroundAudioComponent->SetSound(Sound);
			this->BackgroundAudioComponent->Play();
		}
	}
}

void AMainMenuGameModeBase::StopBackgroundAudio() const
{
	if (this->BackgroundAudioComponent->IsPlaying())
	{
		this->BackgroundAudioComponent->Stop();
	}
}
