#include "Map.h"

Map::Map(const std::string& filePath, ManagersData& managersData) :dialog(managersData.dialog), audioManager(managersData.audioManager), resourceManager(managersData.resourceManager), missionsManager(managersData.missionsManager), collectablesUI(managersData.collectablesUI)
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
void Map::Initialize()
{
	audioManager.PlaySFX(enterStepsBuffer);
	earnMetalsBuffer.loadFromFile("../audios/sfx/sfx_earnMetalPoints.ogg");
	interactBuffer.loadFromFile("../audios/sfx/sfx_interact.ogg");
	openDoorBuffer.loadFromFile("../audios/sfx/sfx_openDoor.ogg");
	startBattleBuffer.loadFromFile("../audios/sfx/sfx_startBattle.ogg");
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
		if (asset->GetData().assetType == AssetType::Interactable)
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
	//std::cout << "Checking interaction..." << this << std::endl;
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
				std::cout << "!!!!!!!!!!";
				std::cout << asset->GetData().sprite->getTextureRect().size.x;
				return true;
			}
			break;
		case AssetType::Trigger:

			if (asset->GetData().sprite->getGlobalBounds().findIntersection(playerBounds))
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
			if (asset->GetData().sprite->getGlobalBounds().findIntersection(playerBounds))
			{
				if (isInteractable) 
				{
					dynamic_cast<InteractableAsset*>(asset)->Interact();
					audioManager.PlaySFX(interactBuffer);
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
void Map::EndBattle(bool playerWin,int enemyID)
{
	isInBattle = false;
	delete battle;
	battle = nullptr;	
	if (playerWin)
	{
		std::cout << "You won the battle!" << std::endl;
		Asset* enemy = enemiesAsset[enemyID];
		int increment = static_cast<EnemyAsset*>(enemy)->enemyBattleData.metalsAmount;
		EraseAsset(enemy);
		enemiesAsset[enemyID] = nullptr;
		/*assetsObjects.erase(std::remove(assetsObjects.begin(), assetsObjects.end(), enemiesAsset[enemyID]), assetsObjects.end());
		assets.erase(std::remove(assets.begin(), assets.end(), enemiesAsset[enemyID]->GetSprite()), assets.end());
		delete enemiesAsset[enemyID];
		enemiesAsset[enemyID] = nullptr;*/
		PlayBackgroundMusic();
		collectablesUI->AddMetalAmount(increment);
		audioManager.PlaySFX(earnMetalsBuffer);
		missionsManager.CheckGetMetalsMission(collectablesUI->GetMetalAmount());
	}
	else
	{
		std::cout << "You lose the battle!" << std::endl;
		SetPlayerInitPosition({ 950.0f, 100.0f });
		nextMapID = MapID::OldWomanHouse;
		wantsChange = true;
	}
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
	//{ enemy->GetSprite(), 3, 20, enemyLife, 3, enemyID };
	EnemyAsset* enemy = enemiesAsset[enemyID];
	BattleData data = enemy->enemyBattleData;
	battle = new Battle(resourceManager, audioManager, 20, data, [this, enemyID](bool& playerWin, int enemyID) {this->EndBattle(playerWin, enemyID); });
	std::string musicPath = "../audios/battleMusic.ogg";
	audioManager.PlayMusic(musicPath);
	audioManager.PlaySFX(startBattleBuffer);
	//dynamic_cast<TriggerAsset*>(enemyBat)->SetCollision(false);
	isInBattle = true;
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


