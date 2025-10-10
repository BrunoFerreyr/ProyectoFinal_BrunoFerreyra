#include "Asset.h"

Asset::Asset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision)
{
	data.haveCollision = collision;
	data.size = size;
	data.position = pos;

	//pasar dos lineas a funcion.
	data.sprite = new sf::Sprite(*texture);
	data.sprite->setTextureRect(size);

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
}
sf::Sprite* Asset::GetSprite() const
{
	return data.sprite;
}
AssetType Asset::GetType() const
{
	return data.assetType;
}
void Asset::deleteSprite()
{
	delete data.sprite;
}