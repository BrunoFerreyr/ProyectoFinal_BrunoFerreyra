#include "Asset.h"

Asset::Asset(AssetData assetData)
{
	data.haveCollision = assetData.haveCollision;
	data.size = assetData.size;
	data.position = assetData.position;

	//pasar dos lineas a funcion.
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
}/*
bool Asset::setUpSprite(const std::string& filePath)
{
	if (data.texture == nullptr) {
		data.texture = new sf::Texture();
		isTextureCreator = true;
	}
	if (!data.texture->loadFromFile(filePath))
	{
		return false;
	}
	//texture.setSmooth(true);
	data.sprite = new sf::Sprite(*data.texture);
	data.sprite->setTextureRect(data.size);
	return true;
}*/
sf::Sprite* Asset::GetSprite() const
{
	return data.sprite;
}
const AssetData& Asset::GetData() const
{
	return data;
}