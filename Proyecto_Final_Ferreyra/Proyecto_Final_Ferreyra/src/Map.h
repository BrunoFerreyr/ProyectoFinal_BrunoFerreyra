#pragma once
#include <SFML/Graphics.hpp>
#include "Asset.h"
#include "TriggerAsset.h" 
#include "ResourceManager.h"
#include "NPC.h"
#include "Dialog.h"
class Map
{
public:
	Map(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog);
	virtual ~Map() = 0;
	void Draw(sf::RenderWindow& window);
	bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable);
	sf::FloatRect GetBounds();

	std::vector<Interactable*> interactables;
	bool wantsChange = false;
	Map* GetNextMap() const;
	void SetNextMap(Map* map);
	sf::Vector2f GetPlayerInitPosition();
protected:	

	std::vector<sf::Sprite*> assets;
	std::vector<Asset*> assetsObjects;
	Map* nextMap;

	sf::Vector2f playerInitPosition;
	std::vector<Asset*> changeMapCollisions;

	sf::Sprite* floor;
	sf::Texture	textureFloor;
	NPC* npc;
};

