#pragma once
#include "ResourceManager.h"
#include "AudioManager.h"
#include "ButtonAsset.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Scene.h"
#include "MainMenu.h"
class Pause
{
public:
	Pause(ResourceManager& resources, AudioManager& audioManager, sf::RenderWindow& window, Scene*& currentScene,
		MainMenu*& mainMenu);
	~Pause();

	void Update(float deltaTime);
	void Draw();
	void HandleEvents(const sf::Event& event);
	bool GetGamePaused();
	void TogglePause(bool value);
	void ReturnToMainMenu();
	void ExitGame();
	void SetIsOnBattle(bool onBattle);
	void SetIsOnDialog(bool onDialog);

private:
	Scene*& currentScene;
	AudioManager& audioManager;
	MainMenu*& mainMenu;
	sf::RenderWindow& window;

	ButtonAsset* continueButton;
	ButtonAsset* mainMenuButton;
	ButtonAsset* exitButton;
	Slider* musicVolumeSlider;
	Slider* sfxVolumeSlider;

	bool gamePaused;
	bool isOnBattle = false;
	bool isOnDialog = false;

	sf::SoundBuffer enterPauseBuffer;
	sf::SoundBuffer exitPauseBuffer;
};

