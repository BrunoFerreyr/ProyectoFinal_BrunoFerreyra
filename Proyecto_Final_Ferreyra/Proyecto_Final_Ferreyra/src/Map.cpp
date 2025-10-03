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
void Map::Update(float deltaTime)
{
	//std::cout << "update..." << this << std::endl;
	if (assetsObjects.empty()) return;
	for (auto asset : assetsObjects)
	{
		if (asset->GetType() == AssetType::Trigger)
		{
			dynamic_cast<TriggerAsset*>(asset)->IdleAnimation(deltaTime);
		}
	}
}
void Map::Draw(sf::RenderWindow& window)
{
	//std::cout << "draw..." << this << std::endl;

	if (floor)
	{
		window.draw(*floor);
	}	
	if (assets.empty()) return;

	for (auto asset : assets)
	{
		window.draw(*asset);
	}
	if(npc != nullptr)//DO solucionar esto y agregar siguientes mapas, luego gameplay de gameloop
	window.draw(*npc->sprite);
}
bool Map::CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable)
{
	//std::cout << "Checking interaction..." << this << std::endl;
	
	if (!isInteractable) 
	{		
		/*if (assets.empty()) return false;

		for (auto asset : assets)
		{
			if (asset->getGlobalBounds().findIntersection(playerBounds))
			{
				return true;
			}
		}*/
		for (auto asset : assetsObjects)
		{
			switch (asset->GetType()) {
			case AssetType::Static:
				
				if (asset->GetSprite()->getGlobalBounds().findIntersection(playerBounds))
				{
					std::cout << "!!!!!!!!!!";
					asset->GetSprite()->setColor(sf::Color::Red);
					std::cout << asset->GetSprite()->getTextureRect().size.x;
					return true;
				}
				break;
			case AssetType::Trigger:
				
				if (asset->GetSprite()->getGlobalBounds().findIntersection(playerBounds))
				{
					//dynamic_cast<TriggerAsset*>(asset)->OnTriggerEnter();

					if (!asset->GetIsInteractable())
					{
						dynamic_cast<TriggerAsset*>(asset)->OnTriggerEnter();
					}
					else 
					{
						asset->Interact();
					}
				}			
				//std::cout << "Trigger asset..." << std::endl;			
				break;
			default:				

				break;
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

MapID& Map::GetNextMap() 
{
	return nextMapID;
}
void Map::SetNextMap(MapID& map)
{
	nextMapID = map;
}
sf::Vector2f Map::GetPlayerInitPosition()
{
	return playerInitPosition;
}