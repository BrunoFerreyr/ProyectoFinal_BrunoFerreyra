#pragma once
#include "ResourceManager.h"

#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "MainMenu.h"
class Pause
{
public:
	Pause(ResourceManager& resources, sf::RenderWindow& window, Scene*& currentScene,
		MainMenu*& mainMenu);
	~Pause();

	void Input();
	void Draw();
	void HandleEvents(const sf::Event& event);
	bool GetGamePaused();
	void PauseGame();
	void UnpauseGame();
	void SetIsOnBattle(bool onBattle);
private:

	Scene*& currentScene;
	MainMenu*& mainMenu;
	sf::RenderWindow& window;

	sf::Sprite* pauseBackground;
	sf::Sprite* continueButton;
	sf::Sprite* mainMenuButton;

	bool gamePaused;
	bool isOnBattle = false;
};

