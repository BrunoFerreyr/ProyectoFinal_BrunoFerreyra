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
	void SetWantsChange(bool value);
	bool GetWantsChange() const;
	MapID& GetNextMap();
	sf::Vector2f GetPlayerInitPosition();
	bool GetIsInBattle() const;
	
protected:	
	
	void CreateAssets();
	virtual void PlayBackgroundMusic();
	void SetPlayerInitPosition(const sf::Vector2f pos);
	void AddSpriteToRender(sf::Sprite* sprite);
	void LoadLevel(MapID, sf::Vector2f);
	void LoadBattle(int enemyLife, int enemyID);
	void EndBattle(bool playerWin, int enemyID);
	void EraseAsset(Asset*& asset);

	bool wantsChange = false;

	std::vector<sf::Sprite*> assets;
	std::vector<Asset*> assetsObjects;
	MapID nextMapID;
	std::vector<MapID> nextMapsIDs;

	sf::Vector2f playerInitPosition;

	std::map<int, EnemyAsset*> enemiesAsset;
	std::map<int, sf::Vector2f> enemiesPosition;
	std::map<int, BattleData> enemiesData;

	sf::Sprite* floor;
	sf::Texture	textureFloor;
	Dialog* dialog;
	AudioManager& audioManager;
	Battle* battle;
	ResourceManager& resourceManager;
	MissionsManager& missionsManager;
	CollectablesUI* collectablesUI;

	bool isInBattle = false;

	sf::SoundBuffer enterStepsBuffer;
	sf::SoundBuffer earnMetalsBuffer;
	sf::SoundBuffer interactBuffer;
	sf::SoundBuffer openDoorBuffer;
	sf::SoundBuffer startBattleBuffer;
};

