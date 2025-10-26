#include "LevelCave.h"

LevelCave::LevelCave(const std::string& filePath, ManagersData& managersData, std::function<void()> resetPositions)
	: Map(filePath, managersData,resetPositions)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	firstTimePosition = { 950.0f, 100.0f };
	playerInitPosition = firstTimePosition;
	goToCamp = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 900.0f, -100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, false, nullptr, AssetType::Static}, [this]() { this->LoadCamp(); });

	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 5.27f, 100 * 1.4f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 550.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.48f, 100 * 1.35f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 686.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 2.24f, 100 * 1.4f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1040.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 2.41f, 100 * 1.4f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 1147.0f, 157.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.4f, 100 * 6.32f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 620.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 12.80f, 100 * 1.7f)), true, false ,nullptr ,AssetType::Static }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 115.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100 * 1.6f, 100 * 6.08f)), true, false ,nullptr ,AssetType::Static }));

	assetsObjects.push_back(goToCamp);
	
	nextMapsIDs.push_back(MapID::Camp);

	enterStepsBuffer.loadFromFile("../../res/audios/sfx/sfx_enterGroundSteps.ogg");

	this->CreateAssets();
}
LevelCave::~LevelCave()
{
	goToCamp = nullptr;
}
void LevelCave::Initialize()
{
	PlayBackgroundMusic();
	Map::Initialize();
}
void LevelCave::LoadCamp()
{
	nextMapID = MapID::Camp;
	wantsChange = true;
}
void LevelCave::PlayBackgroundMusic()
{
	std::string musicPath = "../../res/audios/caveMusic.ogg";
	audioManager.PlayMusic(musicPath);
}