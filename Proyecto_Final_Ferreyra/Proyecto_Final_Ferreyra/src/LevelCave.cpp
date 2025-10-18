#include "LevelCave.h"

LevelCave::LevelCave(const std::string& filePath, ManagersData& managersData)
	: Map(filePath, managersData)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);

	playerInitPosition = { 950.0f, 100.0f };
	goToCamp = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 300.0f, -100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadCamp(); });
	assetsObjects.push_back(goToCamp);
	
	nextMapsIDs.push_back(MapID::Camp);
	this->CreateAssets();
}
LevelCave::~LevelCave()
{
}
void LevelCave::Initialize()
{
	PlayBackgroundMusic();
}
void LevelCave::LoadCamp()
{
	nextMapID = MapID::Camp;
	wantsChange = true;
	//necesito agregar todas las escenas en map current scenes.
	//tener un enum con los nombres, y adentro de cada coso pones current dependiendo de a donde va
}
void LevelCave::PlayBackgroundMusic()
{
	std::string musicPath = "../audios/caveMusic.ogg";
	audioManager->PlayMusic(musicPath);
}