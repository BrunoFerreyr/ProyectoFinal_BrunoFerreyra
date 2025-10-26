#include "Woods01.h"

Woods01::Woods01(const std::string& filePath, ManagersData& managersData, std::function<void()> resetPositions) : Map(filePath, managersData,resetPositions)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	firstTimePosition = { 1120.0f, 530.0f };
	goToCamp = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{1275.0f, 514.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true , false, nullptr }, [this]() { this->LoadLevel(MapID::Camp, firstTimePosition); });
	goToWoods02 = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 960.0f, -100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, false, nullptr }, [this]() { this->LoadLevel(MapID::Woods02, { 1010.0f, 62.0f }); });
	
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 7.5f, 100 * 1.4f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 750.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.9f, 100 * 0.4f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1155.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 2.26f, 100 * 0.4f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1230.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 0.56f, 100 * 4.86f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1226.0f, 609.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 0.56f, 100 * 1.14f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 660.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 12.80f, 100 * 0.43f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 308.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 0.68f, 100 * 3.77f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 135.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.54f, 100 * 1.47f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 457.0f, 420.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 7.70f, 100 * 0.3f)), true, false ,nullptr ,AssetType::Static }));

	assetsObjects.push_back(goToCamp);
	assetsObjects.push_back(goToWoods02);
	playerInitPosition = firstTimePosition;

	nextMapsIDs.push_back(MapID::Camp);
	nextMapsIDs.push_back(MapID::Woods02);

	enemiesAsset[1] = nullptr;
	enemiesData[1] = { nullptr, 3.0f, 10, 20, 3, 1 , 2 }; 
	enemiesPosition[1] = { 600.0f, 540.0f };
	enemiesAsset[2] = nullptr; 
	enemiesData[2] = { nullptr, 2.5f, 15, 25, 3, 2 , 5 }; 
	enemiesPosition[2] = { 1030.0f, 241.0f };

	enterStepsBuffer.loadFromFile("../../res/audios/sfx/sfx_enterGrassSteps.ogg");

	this->CreateAssets();
}

Woods01::~Woods01()
{
	goToCamp = nullptr;
	goToWoods02 = nullptr;
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
	std::string musicPath = "../../res/audios/woodsMusic.ogg";
	audioManager.PlayMusic(musicPath);
}

