#pragma once
#include "Asset.h"

class MapChangeAsset : public Asset
{
	MapChangeAsset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision);
	~MapChangeAsset() override;

	bool SetCollision(bool collision);
	bool GetCollision() const;

	//Map* nextMap;
};

