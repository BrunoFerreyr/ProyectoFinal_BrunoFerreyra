#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
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
	int maxSfxPoolSize = 5;

	sf::Music currentMusic;
	sf::SoundBuffer testBuffer;
	std::vector <sf::Sound> sfxPool;
	std::string actualMusicPath;
};

