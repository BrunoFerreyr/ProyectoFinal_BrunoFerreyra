#pragma once
#include <SFML/Graphics.hpp>
#include "AssetType.h"

class Asset
{
public:
	Asset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision);
	virtual ~Asset();

	bool setUpSprite(const std::string&);
	void deleteSprite();
	sf::Sprite* GetSprite() const;
	virtual AssetType GetType() const;

protected:
	bool haveCollision;
	sf::Sprite* sprite;
	sf::Vector2f position;
	sf::IntRect size;
	sf::Texture* texture;	
	AssetType assetType = AssetType::Static;
	bool isTextureCreator = false;
};