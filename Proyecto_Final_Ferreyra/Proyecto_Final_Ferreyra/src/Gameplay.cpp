#include "Gameplay.h"
Gameplay::Gameplay(sf::RenderWindow& window, Player* player, Pause& pauseManager, ManagersData& managers)
	: Scene(window),
	player(player),
	pauseManager(pauseManager),
	managersData(managers)
{
	levelCave = new LevelCave("../textures/caveFloor.png", managers);
	house = new Level01("../textures/floor.png", managers);
	camp = new Level02("../textures/woodsFloor.png", managers);
	woods01 = new Woods01("../textures/woods/woods01Floor.png", managers);
	woods02 = new Woods02("../textures/woods/woods02Floor.png", managers);
	woods03 = new Woods03("../textures/woods/woods03Floor.png", managers, [this]() { this->OnEndEvent(); });

	maps.emplace(MapID::Cave, levelCave);
	maps.emplace(MapID::OldWomanHouse,house);
	maps.emplace(MapID::Camp,camp);
	maps.emplace(MapID::Woods01, woods01);
	maps.emplace(MapID::Woods02, woods02);
	maps.emplace(MapID::Woods03, woods03);

	currentMap = levelCave;
	player->SetCurrentMap(currentMap, { 400.0f, 400.0f });
	nextSceneID = SceneID::MainMenu;
}
Gameplay::~Gameplay()
{
	currentMap = nullptr;
	for (auto value : maps) 
	{
		delete value.second;
	}
	levelCave = nullptr;
	house = nullptr;
	camp = nullptr;
	woods01 = nullptr;
	woods02 = nullptr;
	woods03 = nullptr;

	maps.clear();
}
void Gameplay::Initialize()
{
	currentMap->Initialize();
}
void Gameplay::Input()
{
	if (pauseManager.GetGamePaused() || currentMap->GetIsInBattle())
	{
		return;
	}

	player->Input();
}
void Gameplay::Update(float deltaTime)
{
	currentMap->Update(deltaTime);

	if (currentMap->GetWantsChange())
	{
		currentMap->SetWantsChange(false);
		Map* map = maps.find(currentMap->GetNextMap())->second;
		currentMap = map;
		currentMap->Initialize();
		player->SetCurrentMap(currentMap, currentMap->GetPlayerInitPosition());
		return;
	}

	if (pauseManager.GetGamePaused())
	{
		pauseManager.Update(deltaTime);
		return;
	}
	if (currentMap->GetIsInBattle())
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
		pauseManager.SetIsOnBattle(false);
	}
	
	if (pauseManager.GetGamePaused())
	{ 
		return;
	}
	player->HandleEvents(event);	
}
void Gameplay::OnEndEvent() 
{
	SetWantsExit(true);
}