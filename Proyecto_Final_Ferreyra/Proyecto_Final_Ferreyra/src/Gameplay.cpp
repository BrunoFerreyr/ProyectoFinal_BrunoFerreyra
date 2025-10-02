#include "Gameplay.h"
Gameplay::Gameplay(sf::RenderWindow& window, ResourceManager& resources, Player* player, Dialog* dialog)
	: Scene(window),
	player(player),
	dialog(dialog)
{
	level01 = new Level01("../textures/floor.png", resources, *dialog);
	level02 = new Level02("../textures/woodsFloor.png", resources, *dialog);
	level01->SetNextMap(level02);

	maps.push_back(level01);
	maps.push_back(level02);

	//maps.emplace(MapID::OldWomanHouse, level01);
	//maps.emplace(MapID::Woods01, level02);
	//currentMap = maps[MapID::OldWomanHouse];
	currentMap = level01;
	player->SetCurrentMap(currentMap, { 400.0f, 400.0f });
	//DO seguir documento, empezar logica de batalla, pensar en tema sobre posiciones.
}
Gameplay::~Gameplay()
{
	for (auto value : maps) 
	{
		delete value;
	}
	maps.clear();
}
void Gameplay::Input()
{
	player->Input();
}
void Gameplay::Update(float deltaTime)
{
	if (currentMap->wantsChange) //DO pasar logica de cambio al mapa, asi podemos acceder al evento
	{
		currentMap->wantsChange = false;
		Map* map = currentMap->GetNextMap();// ver porque no asigna
		currentMap = map;
		player->SetCurrentMap(currentMap, currentMap->GetPlayerInitPosition());
		return;
	}
	player->Update(deltaTime);
}
void Gameplay::Draw()
{
	currentMap->Draw(window);
	//std::cout << currentMap << std::endl;
	//map->Draw(window);
	player->Draw(window);
	dialog->Draw(window);
}
void Gameplay::HandleEvents(const sf::Event& event)
{
	player->HandleEvents(event);
	if (const auto keyEvent = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyEvent->code == sf::Keyboard::Key::P)
		{
			//currentMap = maps[MapID::Woods01];
			//player->SetCurrentMap(currentMap);
		}		
	}
	if (const auto keyEvent = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyEvent->code == sf::Keyboard::Key::H)
		{
			//currentMap = maps[MapID::OldWomanHouse];
			//player->SetCurrentMap(currentMap);
		}
	}
}
Map* Gameplay::GetCurrentMap() const
{
	return currentMap;
}