#pragma once
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "Dialog.h"
#include "ResourceManager.h"
#include "LevelCave.h"
#include "Level01.h"
#include "Level02.h"
#include "Woods01.h"
#include "Woods02.h"
#include "Woods03.h"
#include "Pause.h"
class Gameplay : public Scene
{
public:
	Gameplay(sf::RenderWindow& window, Player* player, Pause& pauseManager, ManagersData& managers, std::function<void()> onEnd);
	~Gameplay() override;

	void Initialize() override;
	void Input() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void HandleEvents(const sf::Event& event) override;

	Map* GetCurrentMap() const;

private:
	void OnEndEvent();
	Player* player;
	//Map* map;

	//std::vector<Map*> maps;
	std::map<MapID,Map*> maps;
	Map* currentMap;
	LevelCave* levelCave;
	Level01* level01;
	Level02* level02;
	Woods01* woods01;
	Woods02* woods02;
	Woods03* woods03;

	Pause& pauseManager;
	ManagersData& managersData;
	bool gameStarted = false;
	std::function<void()> onEndGame;
};
