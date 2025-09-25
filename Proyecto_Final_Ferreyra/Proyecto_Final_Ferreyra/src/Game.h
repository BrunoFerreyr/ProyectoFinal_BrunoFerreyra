#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "ResourceManager.h"
#include "Dialog.h"
#include "Scene.h"

class Game
{
private:
	void Initialize();
	void GameLoop();
	void DeInitialize();
	void CreateWindow();
	void GetFont();
	void CreatePlayer();
	void CreateMap();
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
	std::vector<Map*> maps;
	ResourceManager resourceManager;
	Dialog* dialog;
	sf::Font font;

	std::map<SceneID, Scene*> scenes;
	Scene* currentScene;

public:
	Game();
	~Game();
	void Play();
};

