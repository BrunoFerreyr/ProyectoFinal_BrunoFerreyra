#include "Woods03.h"
Woods03::Woods03(const std::string& filePath, ManagersData& managersData, std::function<void()> onEnd, std::function<void()> resetPositions) : Map(filePath, managersData, resetPositions), onEndGame(onEnd)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	firstTimePosition = { 1170.0f, 250.0f };
	goToWoods02 = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{1275.0f, 50.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, false, nullptr }, [this]() { this->LoadLevel(MapID::Woods02, firstTimePosition); });
	castleEntranceDoor = new InteractableAsset({ &resourceManager.GetTexture("../textures/woods/castleEntranceDoor.png", false, sf::IntRect()), sf::Vector2f{ 100.0f, 155.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(118, 390)), true, true ,nullptr }, [this]() {this->CastleEntranceDoorInteraction(); });
	castleEntranceDoorCollision = new Asset({ &resourceManager.GetTexture("../textures/woods/castleEntranceDoor.png", false, sf::IntRect()), sf::Vector2f{ 100.0f, 155.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(80, 390)), true, false ,nullptr });
	assetsObjects.push_back(new TriggerAsset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 155.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 0.5f, 100 * 3.9f)), true , false, nullptr }, [this]() { this->EndGame(); }));
	
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 2.34f, 100 * 1.89f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 235.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 5.19f, 100 * 1.47f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 745.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 5.36f, 100 * 0.5f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1230.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 0.52f, 100 * 3.07f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1230.0f, 440.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 0.52f, 100 * 2.83f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 231.0f, 672.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 10.47f, 100 * 0.53f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 513.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 2.28f, 100 * 2.10f)), true, false ,nullptr ,AssetType::Static }));

	assetsObjects.push_back(goToWoods02);
	assetsObjects.push_back(castleEntranceDoor);
	assetsObjects.push_back(castleEntranceDoorCollision);

	playerInitPosition = firstTimePosition;

	nextMapsIDs.push_back(MapID::Woods02);

	enemiesAsset[1] = nullptr; 
	enemiesData[1] = { nullptr, 4, 20, 40, 5, 1 , 4}; 
	enemiesPosition[1] = { 866.0f, 178.0f };
	enemiesAsset[2] = nullptr; 
	enemiesData[2] = { nullptr, 3, 25, 45, 6, 2 , 4}; 
	enemiesPosition[2] = { 287.0f, 295.0f };

	enterStepsBuffer.loadFromFile("../../res/audios/sfx/sfx_enterGrassSteps.ogg");

	this->CreateAssets();
}

Woods03::~Woods03()
{
	goToWoods02 = nullptr;
	castleEntranceDoor = nullptr;
	castleEntranceDoorCollision = nullptr;
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
	Map::Initialize();
}

void Woods03::PlayBackgroundMusic()
{
	std::string musicPath = "../../res/audios/woodsMusic.ogg";
	audioManager.PlayMusic(musicPath);
}

void Woods03::CastleEntranceDoorInteraction()
{
	if (missionsManager.HasCastleEntranceKey())
	{
		EraseAsset(castleEntranceDoor);
		EraseAsset(castleEntranceDoorCollision);
		audioManager.PlaySFX(openDoorBuffer);
	}
	else
	{
		dialog->Start(101, 101, nullptr);
	}
}
void Woods03::EndGame() 
{
	dialog->Start(17, 18, onEndGame);	
}
