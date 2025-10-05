#pragma once
#include <SFML/Graphics.hpp>
#include "Asset.h"
#include "TriggerAsset.h" 
#include "InteractableAsset.h"
#include "ResourceManager.h"
#include "NPC.h"
#include "Dialog.h"
#include "MapID.h"

class Map
{
public:
	Map(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog);
	virtual ~Map() = 0;
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable);
	sf::FloatRect GetBounds();

	bool wantsChange = false;
	MapID& GetNextMap();
	void SetNextMap(MapID& map);
	sf::Vector2f GetPlayerInitPosition();
protected:	
	
	void SetPlayerInitPosition(const sf::Vector2f pos);
	std::vector<sf::Sprite*> assets;
	std::vector<Asset*> assetsObjects;
	//Map* nextMap;
	MapID nextMapID;
	std::vector<MapID> nextMapsIDs;

	sf::Vector2f playerInitPosition;
	std::vector<Asset*> changeMapCollisions;

	sf::Sprite* floor;
	sf::Texture	textureFloor;
	Dialog* dialog;
};

