#include "AudioManager.h"

AudioManager::AudioManager()	
{
	// Inicializar volúmenes predeterminados
	musicVolume = 50.f;
	sfxVolume = 50.f;
}
AudioManager::~AudioManager()
{
	if (currentMusic.getStatus() == sf::Music::Status::Playing)
	{
		currentMusic.stop();
		
	}
	delete currentSfx;
}
void AudioManager::PlayMusic(std::string& path) {
	/*if (currentMusic != nullptr && currentMusic->getStatus() == sf::Music::Status::Playing) {
		currentMusic->stop();
	}*/
	if (currentMusic.getStatus() == sf::Music::Status::Playing)
	{
		currentMusic.stop();
	}

	currentMusic.openFromFile(path);
	currentMusic.setVolume(musicVolume);
	currentMusic.setLooping(true);
	currentMusic.play();
}

// Reproducir SFX
void AudioManager::PlaySFX(sf::SoundBuffer& sfx) 
{
    currentSfx->setBuffer(sfx);
   // sound.setVolume(sfxVolume);
    currentSfx->play();    
}

// Ajustar volumen global
void AudioManager::SetMusicVolume(float volume) {
    musicVolume = volume;    
    currentMusic.setVolume(musicVolume);
}

void AudioManager::SetSFXVolume(float volume) {
    sfxVolume = volume;
	currentSfx->setVolume(sfxVolume);
}

float AudioManager::GetMusicVolume() const { return musicVolume; }
float AudioManager::GetSFXVolume() const { return sfxVolume; }