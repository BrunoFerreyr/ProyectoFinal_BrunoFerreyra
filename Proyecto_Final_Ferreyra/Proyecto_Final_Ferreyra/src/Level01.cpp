#include "Level01.h"

Level01::Level01(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& audioManager) : Map(filePath, resourceManager, dialog, audioManager)
{
	//floor = nullptr;

	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{ 0.0f ,720.0f - 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true));
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 578.0f ,720.0f - 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true));
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/wallup.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(1280, 68)), true));
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/wallleft.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true));
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/wallright.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 68.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true));

	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/bed.png", false, sf::IntRect()), sf::Vector2f{ 100.0f, 100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100, 180)), true));
	goToWoods = new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 720.0f, 720.0f - 20.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, [this]() { this->LoadNextMap(); });
	assetsObjects.push_back(goToWoods);

	assetsObjects.push_back(new InteractableAsset(&resourceManager.GetTexture("../textures/oldWoman.png", false, sf::IntRect()), sf::Vector2f{ 600.0f, 600.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(57, 90)), true, [this]() {this->StartDialog(); }));

	for (auto asset : assetsObjects)
	{
		assets.push_back(asset->GetSprite());
	}

	playerInitPosition = {1280.0f - 680.0f, 720.0f - 150.0f };

	nextMapsIDs.push_back(MapID::Camp);
	SetNextMap(nextMapsIDs[0]);

	
	//audioManager.PlayMusic(musicPath);
}
Level01::~Level01()
{
}
void Level01::LoadNextMap()
{
	nextMapID = MapID::Camp;
	wantsChange = true;
}
void Level01::StartDialog()
{
	dialog->Start(0,3);
}
void Level01::PlayBackgroundMusic()
{
	std::string musicPath = "../audios/houseMusic.ogg";
	audioManager->PlayMusic(musicPath);
}



