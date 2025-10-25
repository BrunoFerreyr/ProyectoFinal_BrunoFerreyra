#include "AudioManager.h"

AudioManager::AudioManager()
{
	// Inicializar volúmenes predeterminados
	actualMusicPath = "";
	musicVolume = 50.f;
	sfxVolume = 50.f;	

	testBuffer.loadFromFile("../audios/caveMusic.ogg");

	for (int i = 0; i < maxSfxPoolSize; i++) 
	{
		sfxPool.push_back(sf::Sound(testBuffer));
	}
}
AudioManager::~AudioManager()
{
	if (currentMusic.getStatus() == sf::Music::Status::Playing)
	{
		currentMusic.stop();
	}
}

void AudioManager::PlayMusic(std::string& path) 
{
	if (actualMusicPath == path && currentMusic.getStatus() == sf::Music::Status::Playing)
	{
		return;
	}

	actualMusicPath = path;
	if (currentMusic.getStatus() == sf::Music::Status::Playing)
	{
		currentMusic.stop();
	}

	currentMusic.openFromFile(path);
	currentMusic.setVolume(musicVolume);
	currentMusic.setLooping(true);
	currentMusic.play();
}
void AudioManager::PlaySFX(sf::SoundBuffer& sfx) 
{		
	for (int i = 0; i < sfxPool.size(); i++)
	{		
		if (sfxPool[i].getStatus() != sf::Sound::Status::Playing)
		{
			sfxPool[i].setBuffer(sfx);
			sfxPool[i].play();
			return;
		}
	}	
}

void AudioManager::SetMusicVolume(float volume) 
{
    musicVolume = volume * 100;    
    currentMusic.setVolume(musicVolume);
}
void AudioManager::SetSFXVolume(float volume) 
{
    sfxVolume = volume * 100;
	for (int i = 0; i < sfxPool.size(); i++)
	{
		sfxPool[i].setVolume(sfxVolume);
	}
}

float AudioManager::GetMusicVolume() const 
{ 
	return musicVolume; 
}
float AudioManager::GetSFXVolume() const 
{
	return sfxVolume;
}