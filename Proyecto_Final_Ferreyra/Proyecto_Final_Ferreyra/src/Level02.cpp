#include "Level02.h"

Level02::Level02(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog) : Map(filePath, resourceManager, dialog)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);

	/*assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/bed.png", false, sf::IntRect()), sf::Vector2f{100.0f, 100.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100, 180)), true));

	for (auto asset : assetsObjects)
	{
		assets.push_back(asset->sprite);
	}*/
}

Level02::~Level02()
{
}
