#include "Level02.h"

Level02::Level02(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& audioManager) : Map(filePath, resourceManager, dialog, audioManager)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);

	goToHouse = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 380.0f, -100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadHouse(); });
	goToCave = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 400.0f, 700.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadCave(); });
	goToWoods01 = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ -100.0f, 720.0f - 600.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadWoods01(); });
	enemyBat = new TriggerAsset(&resourceManager.GetTexture("../textures/Enemy.png", false, sf::IntRect()), sf::Vector2f{ 600.0f, 400.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(120, 130)), true, [this]() { this->LoadBattle(20, enemyBat); });

	assetsObjects.push_back(goToHouse);
	assetsObjects.push_back(goToCave);
	assetsObjects.push_back(goToWoods01);
	assetsObjects.push_back(enemyBat);

	playerInitPosition = { 950.0f, 100.0f };
	nextMapsIDs.push_back(MapID::OldWomanHouse);
	nextMapsIDs.push_back(MapID::Cave);
	nextMapsIDs.push_back(MapID::Woods01);

	for (auto asset : assetsObjects)
	{
		assets.push_back(asset->GetSprite());
	}
}

Level02::~Level02()
{
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
void Level02::LoadBattle(int enemyLife, Asset* enemy)
{
	battle = new Battle(resourceManager, 20, enemyLife, enemy, [this](bool playerWin) {this->EndBattle(playerWin); });
	dynamic_cast<TriggerAsset*>(enemyBat)->SetCollision(false);
	isInBattle = true;
}
