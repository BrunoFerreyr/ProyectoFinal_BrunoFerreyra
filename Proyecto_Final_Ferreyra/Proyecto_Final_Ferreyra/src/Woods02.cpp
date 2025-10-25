#include "Woods02.h"
Woods02::Woods02(const std::string& filePath, ManagersData& managersData) : Map(filePath, managersData)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	goToWoods01 = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{935.0f, 715.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, true, nullptr }, [this]() { this->LoadLevel(MapID::Woods01, {935.0f, 620.0f}); });
	goToWoods03 = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ -100.0f, 156.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, true, nullptr }, [this]() { this->LoadLevel(MapID::Woods03, { 120.0f, 156.0f }); });
	
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 7.42f, 100 * 1.44f)), true, true ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 750.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 5.33f, 100 * 0.5f)), true, true ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1230.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 0.54f, 100 * 7.2f)), true, true ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1045.0f, 680.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 2.41f, 100 * 0.42f)), true, true ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 675.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 9.2f, 100 * 0.48f)), true, true ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 310.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 0.64f, 100 * 4.18f)), true, true ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 250.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.63f, 100 * 0.53f)), true, true ,nullptr ,AssetType::Static }));

	assetsObjects.push_back(goToWoods01);
	assetsObjects.push_back(goToWoods03);
	playerInitPosition = { 935.0f, 620.0f };

	nextMapsIDs.push_back(MapID::Woods01);
	nextMapsIDs.push_back(MapID::Woods03);

	
	enemiesAsset[1] = nullptr; // Enemy ID 3
	enemiesData[1] = { nullptr, 4, 20, 40, 5, 1 , 3}; // Enemy ID 3
	enemiesPosition[1] = { 800.0f, 400.0f };
	enemiesAsset[2] = nullptr; // Enemy ID 4
	enemiesData[2] = { nullptr, 4, 25, 45, 6, 2 , 3}; // Enemy ID 4
	enemiesPosition[2] = { 500.0f, 300.0f };

	enterStepsBuffer.loadFromFile("../audios/sfx/sfx_enterGrassSteps.ogg");

	this->CreateAssets();
}

Woods02::~Woods02()
{
}

void Woods02::Initialize()
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
	Map::Initialize();
}

void Woods02::PlayBackgroundMusic()
{
	std::string musicPath = "../audios/woodsMusic.ogg";
	audioManager.PlayMusic(musicPath);
}