#include "Woods01.h"

Woods01::Woods01(const std::string& filePath, ManagersData& managersData) : Map(filePath, managersData)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	goToCamp = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{1275.0f, 514.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true , true, nullptr }, [this]() { this->LoadLevel(MapID::Camp, { 1180.0f, 530.0f }); });
	goToWoods02 = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 960.0f, -100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, true, nullptr }, [this]() { this->LoadLevel(MapID::Woods02, { 1010.0f, 62.0f }); });
	assetsObjects.push_back(goToCamp);
	assetsObjects.push_back(goToWoods02);
	playerInitPosition = { 1180.0f, 530.0f };

	nextMapsIDs.push_back(MapID::Camp);
	nextMapsIDs.push_back(MapID::Woods02);

	enemiesAsset[1] = nullptr; // Enemy ID 1
	enemiesData[1] = { nullptr, 3.0f, 10, 30, 3, 1 , 2 }; // Enemy ID 1
	enemiesPosition[1] = { 900.0f, 400.0f };
	enemiesAsset[2] = nullptr; // Enemy ID 2
	enemiesData[2] = { nullptr, 3, 15, 30, 4, 2 , 5 }; // Enemy ID 1
	enemiesPosition[2] = { 600.0f, 300.0f };

	enterStepsBuffer.loadFromFile("../audios/sfx/sfx_enterGrassSteps.ogg");

	this->CreateAssets();
}

Woods01::~Woods01()
{
}

void Woods01::Initialize()
{
	PlayBackgroundMusic();
	for (auto& pair : enemiesAsset)
	{
		if (pair.second == nullptr)
		{
			int enemyID = pair.first;
			pair.second = new EnemyAsset({ &resourceManager.GetTexture("../textures/Enemy.png", false, sf::IntRect()), enemiesPosition[enemyID], sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(120, 130)), true ,true, nullptr}, enemiesData[enemyID], [this, enemyID]() { this->LoadBattle(30, enemyID); });
			assetsObjects.push_back(pair.second);
			AddSpriteToRender(pair.second->GetSprite());
		}
	}
	Map::Initialize();
}

void Woods01::PlayBackgroundMusic()
{
	std::string musicPath = "../audios/woodsMusic.ogg";
	audioManager.PlayMusic(musicPath);
}

