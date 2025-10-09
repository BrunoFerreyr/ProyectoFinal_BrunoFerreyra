#pragma once
#include "Scene.h"
#include "ResourceManager.h"
#include "AudioManager.h"
class MainMenu : public Scene
{
public:
	MainMenu(sf::RenderWindow& window, ResourceManager& resources, AudioManager& audioManager);
	~MainMenu() override;

	void Input() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void HandleEvents(const sf::Event& event) override;

private:
	AudioManager& audioManager;
	sf::Text* buttonText;
	sf::Text text;

	sf::Sprite* background;

	sf::Sprite* startButton;
};