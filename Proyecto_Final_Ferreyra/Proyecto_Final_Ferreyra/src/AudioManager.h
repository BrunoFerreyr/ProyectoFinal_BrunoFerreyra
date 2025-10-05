#pragma once
#include <SFML/Audio.hpp>
class AudioManager
{
public:
    AudioManager();
	~AudioManager();
	void PlayMusic(std::string& music);
	void PlaySFX(sf::SoundBuffer& sfx);
	void SetMusicVolume(float volume);
	void SetSFXVolume(float volume);
	float GetMusicVolume() const;
	float GetSFXVolume() const;
private:
    float musicVolume = 50.f;
    float sfxVolume = 50.f;

	sf::Music currentMusic;
	sf::Sound* currentSfx;

};

