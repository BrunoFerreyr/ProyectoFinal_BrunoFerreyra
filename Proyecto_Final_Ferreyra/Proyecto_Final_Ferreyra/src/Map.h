#pragma once
#include <SFML/Graphics.hpp>
#include "Asset.h"
#include "ResourceManager.h"
#include "NPC.h"
#include "Dialog.h"
class Map
{
public:
	Map(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog);
	~Map();
	void Draw(sf::RenderWindow& window);
	bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable);
	sf::FloatRect GetBounds();

	std::vector<Interactable*> interactables;

private:
	std::vector<sf::Sprite*> walls;
	std::vector<Asset*> assetsWall;

	std::vector<sf::Sprite*> assets;
	std::vector<Asset*> assetsObjects;

	sf::Sprite* floor;
	sf::Texture	textureFloor;
	NPC* npc;
};

