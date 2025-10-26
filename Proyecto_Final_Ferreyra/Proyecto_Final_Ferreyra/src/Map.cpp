#include "Map.h"

Map::Map(const std::string& filePath, ManagersData& managersData, std::function<void()> resetPositions) :dialog(managersData.dialog), audioManager(managersData.audioManager), resourceManager(managersData.resourceManager), missionsManager(managersData.missionsManager), collectablesUI(managersData.collectablesUI),resetPositionsFunction(resetPositions)
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
	if (battle != nullptr) 
	{
		delete battle;
	}
	enemiesAsset.clear();
}

void Map::Initialize()
{
	audioManager.PlaySFX(enterStepsBuffer);
	earnMetalsBuffer.loadFromFile("../../res/audios/sfx/sfx_earnMetalPoints.ogg");
	interactBuffer.loadFromFile("../../res/audios/sfx/sfx_interact.ogg");
	openDoorBuffer.loadFromFile("../../res/audios/sfx/sfx_openDoor.ogg");
	startBattleBuffer.loadFromFile("../../res/audios/sfx/sfx_startBattle.ogg");
}
void Map::CreateAssets()
{
	for (auto asset : assetsObjects)
	{
		if (asset->GetData().shouldDrawSprite)
		{
			AddSpriteToRender(asset->GetSprite());
		}
	}
}

void Map::Update(float deltaTime)
{
	if (GetIsInBattle())
	{
		battle->Update(deltaTime);
		return;
	}
	if (assetsObjects.empty()) return;
	for (auto asset : assetsObjects)
	{
		if (asset->GetData().assetType == AssetType::Interactable)
		{
			dynamic_cast<InteractableAsset*>(asset)->IdleAnimation(deltaTime);
		}
	}
}
void Map::Draw(sf::RenderWindow& window)
{
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
	dialog->Draw(window);
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
	for (auto asset : assetsObjects)
	{
		if (!asset->GetData().haveCollision || asset->GetData().sprite == nullptr)
		{
			continue;
		}
		switch (asset->GetData().assetType) {
		case AssetType::Static:

			if (asset->GetData().sprite->getGlobalBounds().findIntersection(playerBounds))
			{
				return true;
			}
			break;
		case AssetType::Trigger:

			if (asset->GetData().sprite->getGlobalBounds().findIntersection(playerBounds))
			{
				dynamic_cast<TriggerAsset*>(asset)->OnTriggerEnter();
			}
			break;
		case AssetType::Interactable:
			if (asset->GetData().sprite->getGlobalBounds().findIntersection(playerBounds))
			{
				if (isInteractable) 
				{
					dynamic_cast<InteractableAsset*>(asset)->Interact();
					audioManager.PlaySFX(interactBuffer);
				}				
			}		
		}
	}
	return false;
}

void Map::SetWantsChange(bool value)
{
	wantsChange = value;
}
bool Map::GetWantsChange() const
{
	return wantsChange;
}

MapID& Map::GetNextMap() 
{
	return nextMapID;
}

sf::Vector2f Map::GetPlayerInitPosition() const
{
	return playerInitPosition;
}
bool Map::GetIsInBattle() const
{
	return isInBattle;
}
sf::Vector2f Map::GetFirstTimePosition() const
{
	return firstTimePosition;
}

void Map::PlayBackgroundMusic() 
{
}

void Map::SetPlayerInitPosition(const sf::Vector2f pos)
{
	playerInitPosition = pos;
}

void Map::AddSpriteToRender(sf::Sprite* sprite)
{
	assets.push_back(sprite);
}

void Map::LoadLevel(MapID mapID, sf::Vector2f playerPos)
{
	nextMapID = mapID;
	playerInitPosition = playerPos;
	wantsChange = true;
}

void Map::LoadBattle(int enemyLife, int enemyID)
{
	EnemyAsset* enemy = enemiesAsset[enemyID];
	BattleData data = enemy->enemyBattleData;
	battle = new Battle(resourceManager, audioManager, 20, data, [this, enemyID](bool& playerWin, int enemyID) {this->EndBattle(playerWin, enemyID); });

	std::string musicPath = "../../res/audios/battleMusic.ogg";
	audioManager.PlayMusic(musicPath);
	audioManager.PlaySFX(startBattleBuffer);
	isInBattle = true;
}
void Map::EndBattle(bool playerWin,int enemyID)
{
	isInBattle = false;
	delete battle;
	battle = nullptr;	
	if (playerWin)
	{
		Asset* enemy = enemiesAsset[enemyID];
		int increment = static_cast<EnemyAsset*>(enemy)->enemyBattleData.metalsAmount;
		EraseAsset(enemy);
		enemiesAsset[enemyID] = nullptr;
		
		PlayBackgroundMusic();
		collectablesUI->AddMetalAmount(increment);
		audioManager.PlaySFX(earnMetalsBuffer);
		missionsManager.CheckGetMetalsMission(collectablesUI->GetMetalAmount());
	}
	else
	{
		if (resetPositionsFunction) 
		{
			resetPositionsFunction();
		}
		nextMapID = MapID::Cave;
		wantsChange = true;
	}
}

void Map::EraseAsset(Asset*& asset)
{
	assetsObjects.erase(std::remove(assetsObjects.begin(), assetsObjects.end(), asset), assetsObjects.end());
	if (asset->GetData().shouldDrawSprite) 
	{
		assets.erase(std::remove(assets.begin(), assets.end(), asset->GetSprite()), assets.end());
	}

	delete asset;
	asset = nullptr;
}


