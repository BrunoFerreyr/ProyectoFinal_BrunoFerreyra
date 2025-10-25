#pragma once
#include <SFML/Graphics.hpp>
#include "AssetData.h"

class Asset
{
public:
	Asset(AssetData assetData);
	virtual ~Asset();

	//bool setUpSprite(const std::string&);
	sf::Sprite* GetSprite() const;
	const AssetData& GetData() const;
protected:
	AssetData data;
	bool isTextureCreator = false;
	bool shouldDrawSprite = true;
};