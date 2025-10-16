#include "Gameplay.h"
Gameplay::Gameplay(sf::RenderWindow& window, Player* player, Pause& pauseManager, ManagersData& managers)
	: Scene(window),
	player(player),
	pauseManager(pauseManager),
	managersData(managers)
{
	levelCave = new LevelCave("../textures/caveFloor.png", managers);
	level01 = new Level01("../textures/floor.png", managers);
	level02 = new Level02("../textures/woodsFloor.png", managers);

	maps.emplace(MapID::Cave, levelCave);
	maps.emplace(MapID::OldWomanHouse,level01);
	maps.emplace(MapID::Camp,level02);

	//maps.emplace(MapID::OldWomanHouse, level01);
	//maps.emplace(MapID::Woods01, level02);
	//currentMap = maps[MapID::OldWomanHouse];

	currentMap = levelCave;
	player->SetCurrentMap(currentMap, { 400.0f, 400.0f });
}
Gameplay::~Gameplay()
{
	for (auto value : maps) 
	{
		delete value.second;
	}
	maps.clear();
}
void Gameplay::Initialize()
{
	currentMap->Initialize();
}
void Gameplay::Input()
{
	pauseManager.Input();
	if (pauseManager.GetGamePaused() || currentMap->GetIsInBattle())
	{
		return;
	}

	player->Input();
}
void Gameplay::Update(float deltaTime)
{
	currentMap->Update(deltaTime);

	if (currentMap->wantsChange)
	{
		currentMap->wantsChange = false;
		Map* map = maps.find(currentMap->GetNextMap())->second;
		currentMap = map;
		currentMap->Initialize();
		player->SetCurrentMap(currentMap, currentMap->GetPlayerInitPosition());
		return;
	}

	if (pauseManager.GetGamePaused() || currentMap->GetIsInBattle())
	{
		return;
	}

	player->Update(deltaTime);
}
void Gameplay::Draw()
{
	currentMap->Draw(window);
	if(currentMap->GetIsInBattle())
	{
		return;
	}
	//std::cout << currentMap << std::endl;
	//map->Draw(window);
	managersData.collectablesUI->Draw(window);
	player->Draw(window);
	pauseManager.Draw();
}
void Gameplay::HandleEvents(const sf::Event& event)
{
	pauseManager.HandleEvents(event);
	currentMap->HandleEvents(event);
	if (currentMap->GetIsInBattle())
	{
		pauseManager.SetIsOnBattle(true);
		return;
	}
	else
	{
		pauseManager.SetIsOnBattle(false);//DO
	}
	if (pauseManager.GetGamePaused())
	{ 
		return;
	}
	player->HandleEvents(event);	
}
Map* Gameplay::GetCurrentMap() const
{
	return currentMap;
}