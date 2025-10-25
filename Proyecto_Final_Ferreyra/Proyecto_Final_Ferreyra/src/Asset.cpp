#include "Asset.h"

Asset::Asset(AssetData assetData)
{
	data.haveCollision = assetData.haveCollision;
	data.size = assetData.size;
	data.position = assetData.position;

	data.shouldDrawSprite = assetData.shouldDrawSprite;
	data.sprite = new sf::Sprite(*assetData.texture);
	data.sprite->setTextureRect(assetData.size);
	data.sprite->setPosition(data.position);
}
Asset::~Asset()
{	
	if (data.sprite != nullptr)
	{
		delete data.sprite;
		data.sprite = nullptr;
	}
}
sf::Sprite* Asset::GetSprite() const
{
	return data.sprite;
}
const AssetData& Asset::GetData() const
{
	return data;
}