#include "Map.h"

Map::Map(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog)
{
}
Map::~Map()
{	
	if (assetsObjects.empty()) return;
	for (auto asset : assetsObjects)
	{
		delete asset;
	}
	assets.clear();
	delete floor;
}

void Map::Draw(sf::RenderWindow& window)
{
	std::cout << "draw..." << this << std::endl;

	if (floor)
	{
		window.draw(*floor);
	}	
	if (assets.empty()) return;

	for (auto asset : assets)
	{
		window.draw(*asset);
	}
	window.draw(*npc->sprite);
}
bool Map::CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable)
{
	std::cout << "Checking interaction..." << this << std::endl;
	if (!isInteractable) 
	{		
		if (assets.empty()) return false;	

		for (auto asset : assets)
		{
			if (asset->getGlobalBounds().findIntersection(playerBounds))
			{
				return true;
			}
		}
	}
	else 
	{
		std::cout << "Checking interaction..." << std::endl;
		if (interactables.empty()) return false;
		for (auto interactable : interactables)
		{
			if (interactable->sprite->getGlobalBounds().findIntersection(playerBounds))
			{
				interactable->Interact();
				return true;
			}
		}
	}
	
	return false;
}
