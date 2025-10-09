#include "Map.h"

Map::Map(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& AudioManager) :dialog(&dialog), audioManager(&AudioManager), resourceManager(resourceManager)
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
	if (GetIsInBattle())
	{
		battle->Update(deltaTime);
		return;
	}
	if (assetsObjects.empty()) return;
	for (auto asset : assetsObjects)
	{
		if (asset->GetType() == AssetType::Interactable)
		{
			dynamic_cast<InteractableAsset*>(asset)->IdleAnimation(deltaTime);
		}
	}
}
void Map::Draw(sf::RenderWindow& window)
{
	//std::cout << "draw..." << this << std::endl;
	if (GetIsInBattle())
	{
		battle->Draw(window);
		return;
	}

	if (floor)
	{
		window.draw(*floor);
	}	
	if (assets.empty()) return;

	for (auto asset : assets)
	{
		window.draw(*asset);
	}
}
void Map::HandleEvents(const sf::Event& event)
{
	if (GetIsInBattle())
	{
		battle->HandleEvents(event);
		return;
	}
}
bool Map::CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable)
{
	//std::cout << "Checking interaction..." << this << std::endl;
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
				dynamic_cast<TriggerAsset*>(asset)->OnTriggerEnter();

				/*if (!asset->GetIsInteractable())
				{
					dynamic_cast<TriggerAsset*>(asset)->OnTriggerEnter();
				}
				else
				{
					asset->Interact();
				}*/
			}
			//std::cout << "Trigger asset..." << std::endl;			
			break;
		case AssetType::Interactable:
			if (asset->GetSprite()->getGlobalBounds().findIntersection(playerBounds))
			{
				if (isInteractable) 
				{
					dynamic_cast<InteractableAsset*>(asset)->Interact();
				}
				//std::cout << "Interactable asset..." << std::endl;
				//dynamic_cast<InteractableAsset*>(asset)->Interact();
				//return true;
			}
		default:

			break;
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
void Map::PlayBackgroundMusic() {
}
void Map::SetPlayerInitPosition(const sf::Vector2f pos)
{
	playerInitPosition = pos;
}
bool Map::GetIsInBattle() const
{
	return isInBattle;
}
void Map::EndBattle(bool playerWin,Asset* enemy)
{
	isInBattle = false;
	delete battle;
	battle = nullptr;	
	if (playerWin)
	{
		std::cout << "You won the battle!" << std::endl;
		assetsObjects.erase(std::remove(assetsObjects.begin(), assetsObjects.end(), enemy), assetsObjects.end());
		assets.erase(std::remove(assets.begin(), assets.end(), enemy->GetSprite()), assets.end());
		delete enemy;
		PlayBackgroundMusic();
	}
	else
	{
		std::cout << "You lose the battle!" << std::endl;
		nextMapID = MapID::OldWomanHouse;
		wantsChange = true;
	}
}
