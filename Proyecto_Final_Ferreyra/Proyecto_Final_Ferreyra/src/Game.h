#pragma once
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "ResourceManager.h"
#include "Dialog.h"
#include "Scene.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "Pause.h"
#include "AudioManager.h"

class Game
{
private:
	void Initialize();
	void GameLoop();
	void DeInitialize();
	void CreateWindow();
	void GetFont();
	void CreatePlayer();
	//void CreateMap();
	void Input();
	void HandleEvents();
	void Update();
	void Draw();
	void DestroyWindow();
	void DestroyPlayer();
	void DestroyMaps();

	sf::RenderWindow* window;
	Player* player;
	sf::Clock clockk;
	ResourceManager resourceManager;
	AudioManager audioManager;

	Dialog* dialog;
	sf::Font font;

	std::map<SceneID, Scene*> scenes;
	Scene* currentScene;

	MainMenu* mainMenu;
	Gameplay* gameplay;
	Pause* pauseManager;
	//PauseManager* pauseManager;

public:
	Game();
	~Game();
	void Play();
};

