#pragma once
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "Dialog.h"
#include "ResourceManager.h"
#include "Level01.h"
#include "Level02.h"

enum class MapID
{
	OldWomanHouse,
	Woods01,
};
class Gameplay : public Scene
{
public:
	Gameplay(sf::RenderWindow& window, ResourceManager& resources, Player* player, Dialog* dialog);
	~Gameplay() override;
	void Input() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void HandleEvents(const sf::Event& event) override;

	Map* GetCurrentMap() const;
private:
	Player* player;
	//Map* map;
	Dialog* dialog;		

	//std::vector<Map*> maps;
	std::map<MapID, Map*> maps;
	Map* currentMap;
	Level01* level01;
	Level02* level02;
};
