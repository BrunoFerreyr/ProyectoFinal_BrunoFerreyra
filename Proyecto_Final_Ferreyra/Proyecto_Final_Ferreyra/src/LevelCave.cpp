#include "LevelCave.h"

LevelCave::LevelCave(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& audioManager)
	: Map(filePath, resourceManager, dialog, audioManager)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);

	goToCamp = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 300.0f, -100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadCamp(); });
	playerInitPosition = { 950.0f, 100.0f };

	assetsObjects.push_back(goToCamp);
	for (auto asset : assetsObjects)
	{
		assets.push_back(asset->GetSprite());
	}
	nextMapsIDs.push_back(MapID::Camp);
}
LevelCave::~LevelCave()
{
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