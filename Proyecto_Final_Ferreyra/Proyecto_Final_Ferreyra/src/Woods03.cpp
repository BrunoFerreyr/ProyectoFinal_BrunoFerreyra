#include "Woods03.h"
Woods03::Woods03(const std::string& filePath, ManagersData& managersData) : Map(filePath, managersData)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	goToWoods02 = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{1275.0f, 320.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, true, nullptr }, [this]() { this->LoadLevel(MapID::Woods02, {1205.0f, 340.0f}); });
	assetsObjects.push_back(goToWoods02);
	playerInitPosition = { 1205.0f, 340.0f };

	nextMapsIDs.push_back(MapID::Woods02);

	
	enemiesAsset[1] = nullptr; // Enemy ID 3
	enemiesData[1] = { nullptr, 4, 20, 40, 5, 1 }; // Enemy ID 3
	enemiesPosition[1] = { 800.0f, 400.0f };
	enemiesAsset[2] = nullptr; // Enemy ID 4
	enemiesData[2] = { nullptr, 4, 25, 45, 6, 2 }; // Enemy ID 4
	enemiesPosition[2] = { 500.0f, 300.0f };

	this->CreateAssets();
}

Woods03::~Woods03()
{
}

void Woods03::Initialize()
{
	PlayBackgroundMusic();
	for (auto& pair : enemiesAsset)
	{
		if (pair.second == nullptr)
		{
			int enemyID = pair.first;
			pair.second = new EnemyAsset({ &resourceManager.GetTexture("../textures/Enemy.png", false, sf::IntRect()), enemiesPosition[enemyID], sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(120, 130)), true ,true, nullptr }, enemiesData[enemyID], [this, enemyID]() { this->LoadBattle(30, enemyID); });
			assetsObjects.push_back(pair.second);
			AddSpriteToRender(pair.second->GetSprite());
		}
	}
}

void Woods03::PlayBackgroundMusic()
{
	std::string musicPath = "../audios/woodsMusic.ogg";
	audioManager->PlayMusic(musicPath);
}