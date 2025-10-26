#include "Level02.h"

Level02::Level02(const std::string& filePath, ManagersData& managersData, std::function<void()> resetPositions) : Map(filePath, managersData,resetPositions)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	firstTimePosition = { 590.0f, 580.0f };
	goToHouse = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{900.0f, 50.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true , false, nullptr }, [this]() { this->LoadLevel(MapID::OldWomanHouse, {900.0f, 220.0f}); });
	goToCave = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 590.0f, 700.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, false, nullptr }, [this]() { this->LoadLevel(MapID::Cave, firstTimePosition); });
	goToWoods01 = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ -100.0f, 330.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, false, nullptr }, [this]() { this->LoadLevel(MapID::Woods01, { 64.0f, 330.0f }); });
	woodsDoor = new InteractableAsset({ &resourceManager.GetTexture("../textures/woodsDoor.png", false, sf::IntRect()), sf::Vector2f{ 40.0f, 315.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(41, 136)), true, true ,nullptr }, [this]() {this->WoodsDoorInteraction(); });
	woodsDoorCollision = new Asset({ &resourceManager.GetTexture("../textures/woodsDoor.png", false, sf::IntRect()), sf::Vector2f{ 40.0f, 315.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(22, 136)), true, false ,nullptr ,AssetType::Static });

	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 2.2f, 100* 2.9f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 217.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 10.67f, 100 * 1.2f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1120.0f, 170.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.66f, 100 * 5.52f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 853.0f, 594.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 2.71f, 100 * 1.34f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 695.0f, 673.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.73f, 100 * 0.53f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 423.0f, 676.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.6f, 100 * 0.58f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 587.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 4.29f, 100 * 1.38f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 429.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.70f, 100 * 2.0f)), true, false ,nullptr ,AssetType::Static }));

	assetsObjects.push_back(goToHouse);
	assetsObjects.push_back(goToCave);
	assetsObjects.push_back(goToWoods01);
	assetsObjects.push_back(woodsDoor);
	assetsObjects.push_back(woodsDoorCollision);

	playerInitPosition = firstTimePosition;
	nextMapsIDs.push_back(MapID::OldWomanHouse);
	nextMapsIDs.push_back(MapID::Cave);
	nextMapsIDs.push_back(MapID::Woods01);
	
	enterStepsBuffer.loadFromFile("../../res/audios/sfx/sfx_enterGrassSteps.ogg");

	this->CreateAssets();
}
Level02::~Level02()
{
	goToHouse = nullptr;
	goToCave = nullptr;
	goToWoods01 = nullptr;
	woodsDoor = nullptr;
	woodsDoorCollision = nullptr;
}
void Level02::Initialize()
{
	PlayBackgroundMusic();
	
	Map::Initialize();
}

void Level02::PlayBackgroundMusic()
{
	std::string musicPath = "../../res/audios/caveMusic.ogg";
	audioManager.PlayMusic(musicPath);
}

void Level02::WoodsDoorInteraction()
{
	if (missionsManager.HasWoodsKey())
	{
		EraseAsset(woodsDoor);
		EraseAsset(woodsDoorCollision);
		audioManager.PlaySFX(openDoorBuffer);				
	}
	else
	{
		dialog->Start(100, 100, nullptr);
	}
}
