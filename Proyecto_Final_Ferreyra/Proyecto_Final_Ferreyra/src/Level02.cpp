#include "Level02.h"

Level02::Level02(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& audioManager) : Map(filePath, resourceManager, dialog, audioManager)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);

	goToHouse = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 380.0f, -100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadHouse(); });
	goToCave = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 400.0f, 700.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadCave(); });
	goToWoods01 = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ -100.0f, 720.0f - 600.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadWoods01(); });

	assetsObjects.push_back(goToHouse);
	assetsObjects.push_back(goToCave);
	assetsObjects.push_back(goToWoods01);

	playerInitPosition = { 400.0f, 600.0f };
	nextMapsIDs.push_back(MapID::OldWomanHouse);
	nextMapsIDs.push_back(MapID::Cave);
	nextMapsIDs.push_back(MapID::Woods01);

	for (auto asset : assetsObjects)
	{
		AddSpriteToRender(asset->GetSprite());
	}
	enemyAssets[1] = nullptr; // Enemy ID 1
}

Level02::~Level02()
{
}
void Level02::Initialize()
{
	PlayBackgroundMusic();
	for (auto& pair : enemyAssets)
	{
		if (pair.second == nullptr)
		{			
			int enemyID = pair.first;
			pair.second = new TriggerAsset(&resourceManager.GetTexture("../textures/Enemy.png", false, sf::IntRect()), sf::Vector2f{ 900.0f, 400.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(120, 130)), true, [this, enemyID]() { this->LoadBattle(20, enemyID); });
			assetsObjects.push_back(pair.second);
			AddSpriteToRender(pair.second->GetSprite());
		}
	}
	
}
void Level02::LoadHouse()
{
	nextMapID = MapID::OldWomanHouse;
	playerInitPosition = { 950.0f, 100.0f };
	wantsChange = true;
	//necesito agregar todas las escenas en map current scenes.
	//tener un enum con los nombres, y adentro de cada coso pones current dependiendo de a donde va
}
void Level02::LoadCave()
{
	nextMapID = MapID::Cave;
	SetPlayerInitPosition({ 400.0f, 600.0f });
	wantsChange = true;
	//necesito agregar todas las escenas en map current scenes.
	//tener un enum con los nombres, y adentro de cada coso pones current dependiendo de a donde va
}
void Level02::LoadWoods01()
{
	nextMapID = MapID::Woods01;
	wantsChange = true;
	//necesito agregar todas las escenas en map current scenes.
	//tener un enum con los nombres, y adentro de cada coso pones current dependiendo de a donde va
}
void Level02::LoadBattle(int enemyLife, int enemyID)
{
	Asset* enemy = enemyAssets[enemyID];
	battle = new Battle(resourceManager, 20, enemyLife, enemy, [this, enemyID](bool& playerWin, Asset* enemy) {this->EndBattle(playerWin, enemyID); });
	std::string musicPath = "../audios/battleMusic.ogg";
	audioManager->PlayMusic(musicPath);
	//dynamic_cast<TriggerAsset*>(enemyBat)->SetCollision(false);
	isInBattle = true;
}
void Level02::PlayBackgroundMusic()
{
	std::string musicPath = "../audios/houseMusic.ogg";
	audioManager->PlayMusic(musicPath);
}
