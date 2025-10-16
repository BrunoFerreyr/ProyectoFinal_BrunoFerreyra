#pragma once
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "Dialog.h"
#include "ResourceManager.h"
#include "LevelCave.h"
#include "Level01.h"
#include "Level02.h"
#include "Pause.h"
class Gameplay : public Scene
{
public:
	Gameplay(sf::RenderWindow& window, Player* player, Pause& pauseManager, ManagersData& managers);
	~Gameplay() override;

	void Initialize() override;
	void Input() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void HandleEvents(const sf::Event& event) override;

	Map* GetCurrentMap() const;

private:
	Player* player;
	//Map* map;

	//std::vector<Map*> maps;
	std::map<MapID,Map*> maps;
	Map* currentMap;
	LevelCave* levelCave;
	Level01* level01;
	Level02* level02;
	Pause& pauseManager;
	ManagersData& managersData;
	bool gameStarted = false;
};
