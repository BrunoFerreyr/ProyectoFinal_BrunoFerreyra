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
	virtual ~Map() = 0;
	void Draw(sf::RenderWindow& window);
	virtual bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable);
	sf::FloatRect GetBounds();

	std::vector<Interactable*> interactables;

protected:	
	std::vector<sf::Sprite*> assets;
	std::vector<Asset*> assetsObjects;

	std::vector<Asset*> changeMapCollisions;

	sf::Sprite* floor;
	sf::Texture	textureFloor;
	NPC* npc;
};

