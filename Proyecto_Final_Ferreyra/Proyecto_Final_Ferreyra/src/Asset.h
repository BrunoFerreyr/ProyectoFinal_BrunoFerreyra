#pragma once
#include <SFML/Graphics.hpp>
#include "AssetData.h"

class Asset
{
public:
	Asset(AssetData assetData);
	virtual ~Asset();

	sf::Sprite* GetSprite() const;
	const AssetData& GetData() const;
protected:
	AssetData data;
	bool isTextureCreator = false;
	bool shouldDrawSprite = true;
};