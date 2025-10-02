#include "Level01.h"

Level01::Level01(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog) : Map(filePath, resourceManager, dialog)
{
	//floor = nullptr;
	npc = new NPC("../textures/oldWoman.png", sf::Vector2i(69, 112), resourceManager, dialog);
	interactables.push_back(npc);

	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{ 0.0f ,720.0f - 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true));
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 578.0f ,720.0f - 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true));
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/wallup.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(1280, 68)), true));
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/wallleft.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true));
	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/wallright.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 68.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true));

	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/bed.png", false, sf::IntRect()), sf::Vector2f{ 100.0f, 100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100, 180)), true));
	assetsObjects.push_back(new TriggerAsset(&resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f * 0.5f, 720.0f - 40.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 40)), true, [this]() { this->LoadNextMap(); }));

	for (auto asset : assetsObjects)
	{
		assets.push_back(asset->GetSprite());
	}

	playerInitPosition = {1280.0f * 0.5f, 720.0f - 100.0f };
}
Level01::~Level01()
{
	
}
void Level01::LoadNextMap()
{
	wantsChange = true;
}


