#pragma once
#include "Scene.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "ButtonAsset.h"
#include "Slider.h"

class MainMenu : public Scene
{
public:
	MainMenu(sf::RenderWindow& window, ResourceManager& resources, AudioManager& audioManager);
	~MainMenu() override;

	void Input() override;
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void HandleEvents(const sf::Event& event) override;

private:
	AudioManager& audioManager;
	sf::Text text;

	sf::Sprite* background;

	ButtonAsset* startButton;
	ButtonAsset* controlsButton;
	ButtonAsset* creditsButton;
	ButtonAsset* exitButton;
	Slider* musicVolumeSlider;
	Slider* sfxVolumeSlider;
	sf::Sprite* controlsBackground;
	sf::Sprite* creditsBackground;
	sf::Text* creditsText;
	sf::SoundBuffer testBuffer;
	sf::SoundBuffer testBuffer2;

	bool showCredits = false;
	bool showControls = false;
	void LoadGame();
	void ToggleCredits();
	void ToggleControls();
	void ExitGame();
};