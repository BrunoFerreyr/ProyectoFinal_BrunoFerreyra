#pragma once
#include <SFML/Graphics.hpp>
#include "AssetData.h"

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
	AssetData data;
	bool isTextureCreator = false;
};