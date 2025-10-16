#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Asset.h"
#include "TriggerAsset.h" 
#include "InteractableAsset.h"
#include "EnemyAsset.h"
#include "ManagersData.h"
#include "MapID.h"
#include "Battle.h"

class Map
{
public:
	Map(const std::string& filePath, ManagersData& managersData);
	virtual ~Map() = 0;

	virtual void Initialize() = 0;
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void HandleEvents(const sf::Event& event);
	bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable);
	sf::FloatRect GetBounds();
	bool wantsChange = false;
	MapID& GetNextMap();
	void SetNextMap(MapID& map);
	sf::Vector2f GetPlayerInitPosition();
	virtual void PlayBackgroundMusic();
	bool GetIsInBattle() const;
	void EndBattle(bool playerWin, int enemyID);

protected:	
	
	void SetPlayerInitPosition(const sf::Vector2f pos);
	void AddSpriteToRender(sf::Sprite* sprite);
	std::vector<sf::Sprite*> assets;
	std::vector<Asset*> assetsObjects;
	//Map* nextMap;
	MapID nextMapID;
	std::vector<MapID> nextMapsIDs;

	sf::Vector2f playerInitPosition;
	std::vector<Asset*> changeMapCollisions;
	std::map<int, EnemyAsset*> enemiesAsset;
	std::map<int, sf::Vector2f> enemiesPosition;
	std::map<int, BattleData> enemiesData;
	sf::Sprite* floor;
	sf::Texture	textureFloor;
	Dialog* dialog;
	AudioManager* audioManager;
	Battle* battle;
	ResourceManager& resourceManager;
	MissionsManager& missionsManager;
	CollectablesUI* collectablesUI;
	ManagersData* managersData;

	bool isInBattle = false;
};

