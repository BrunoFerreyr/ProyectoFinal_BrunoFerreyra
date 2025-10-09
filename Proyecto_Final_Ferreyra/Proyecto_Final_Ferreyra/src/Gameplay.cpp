#include "Gameplay.h"
Gameplay::Gameplay(sf::RenderWindow& window, ResourceManager& resources, Player* player, Dialog* dialog, Pause& pauseManager, AudioManager& audioManager)
	: Scene(window),
	player(player),
	dialog(dialog),
	pauseManager(pauseManager)
{
	levelCave = new LevelCave("../textures/caveFloor.png", resources, *dialog,audioManager);
	level01 = new Level01("../textures/floor.png", resources, *dialog,audioManager);
	level02 = new Level02("../textures/woodsFloor.png", resources, *dialog,audioManager);

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

	if (gameStarted == false)
	{
		currentMap->PlayBackgroundMusic();
		gameStarted = true;
	}

	if (currentMap->wantsChange)
	{
		currentMap->wantsChange = false;
		Map* map = maps.find(currentMap->GetNextMap())->second;
		currentMap = map;
		currentMap->PlayBackgroundMusic();
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
	player->Draw(window);
	dialog->Draw(window);
	pauseManager.Draw();
}
void Gameplay::HandleEvents(const sf::Event& event)
{
	pauseManager.HandleEvents(event);
	currentMap->HandleEvents(event);
	if (pauseManager.GetGamePaused() || currentMap->GetIsInBattle())
	{ 
		return;
	}
	player->HandleEvents(event);	
}
Map* Gameplay::GetCurrentMap() const
{
	return currentMap;
}