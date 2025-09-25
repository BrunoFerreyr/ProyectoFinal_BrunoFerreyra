#pragma once
#include <SFML/Graphics.hpp>
class Asset
{
public:
	//Asset(std::string filePath, const sf::Vector2f pos, sf::IntRect size, bool collision);
	Asset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision);
	~Asset();
	bool haveCollision;
	sf::Vector2f position;
	sf::IntRect size;
	sf::Sprite* sprite;
	sf::Texture* texture;
	bool setUpSprite(const std::string&);
	void deleteSprite();
	bool isTextureCreator = false;
};