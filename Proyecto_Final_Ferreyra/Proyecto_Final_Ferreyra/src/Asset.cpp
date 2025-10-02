#include "Asset.h"

/*Asset::Asset(std::string filePath, sf::Vector2f pos, sf::IntRect size, bool collision)
{	
	haveCollision = collision;
	this->size = size;
	position = pos;
	setUpSprite(filePath);
	sprite->setPosition(position);
}*/
Asset::Asset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision)
{
	haveCollision = collision;
	this->size = size;
	position = pos;

	//pasar dos lineas a funcion.
	sprite = new sf::Sprite(*texture);
	sprite->setTextureRect(size);

	sprite->setPosition(position);
}
Asset::~Asset()
{	
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}
bool Asset::setUpSprite(const std::string& filePath)
{
	if (texture == nullptr) {
		texture = new sf::Texture();
		isTextureCreator = true;
	}
	if (!texture->loadFromFile(filePath))
	{
		return false;
	}
	//texture.setSmooth(true);
	sprite = new sf::Sprite(*texture);
	sprite->setTextureRect(size);
	return true;
}
sf::Sprite* Asset::GetSprite() const
{
	return sprite;
}
AssetType Asset::GetType() const
{
	return assetType;
}
void Asset::deleteSprite()
{
	delete sprite;
}