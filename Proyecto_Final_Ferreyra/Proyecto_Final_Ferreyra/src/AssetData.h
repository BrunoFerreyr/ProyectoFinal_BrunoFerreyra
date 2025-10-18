#pragma once
#include <SFML/Graphics.hpp>
#include "AssetType.h"

struct AssetData 
{
	bool haveCollision;
	bool shouldDrawSprite;
	sf::Sprite* sprite;
	sf::Vector2f position;
	sf::IntRect size;
	sf::Texture* texture;
	AssetType assetType = AssetType::Static;
};
