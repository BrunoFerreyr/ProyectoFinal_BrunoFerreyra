#pragma once
#include <SFML/Graphics.hpp>
#include "AssetType.h"

struct AssetData 
{
	sf::Texture* texture;
	sf::Vector2f position;
	sf::IntRect size;
	bool haveCollision;
	bool shouldDrawSprite;
	sf::Sprite* sprite;
	AssetType assetType = AssetType::Static;
};
