#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "ResourceManager.h"
#include "AudioManager.h"
#include "Asset.h"
#include "Bar.h"
#include "BattleData.h"
class Battle
{
public:
	Battle(ResourceManager& resourceManager,AudioManager& audio,int playerLife, const BattleData& data, std::function<void(bool&,int)> callback);
	~Battle();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void HandleEvents(const sf::Event& event);

private:
	void StartBattle();
	void EndBattle();
	
	void ShowKeys();
	void DoAction();

	sf::Keyboard::Key GetCorrectKey() const;
	void UpdateStats();

	bool battleStarted = false;
	bool battleEnded = false;
	bool playerWins = false;
	bool battleActive = false;
	bool shouldTap = false;
	bool isAttacking = false;
	float counter = 0.0f;
	float waitCounter = 0.0f;
	float waitLimit = 3.0f;
	float timeToStart = 3.0f;
	Asset* playerSprite;
	sf::Sprite enemySprite;
	Asset* playerLifeSprite;
	Asset* enemyLifeSprite;
	std::vector<sf::Keyboard::Key> correctKeys;
	std::vector<Asset*> keysAssets;
	std::vector<sf::Sprite*> keysSprites;

	std::vector<char> keysChar;
	std::vector<char> allKeysChar;
	std::vector<sf::Keyboard::Key> allKeys;
	int totalPoints = 0;
	int keyPointValue = 4;
	int inputIndex = 0;
	int playerHealth = 100;
	int enemyHealth = 0;
	BattleData battleData;
	sf::Font font;
	sf::Text* pointsText;
	sf::Text* playerText;
	sf::Text* enemyText;
	std::vector<sf::Text*> keysText;
	sf::Text* roundText;
	Bar* timeBar;
	Asset* timeBarBackground;
	std::function<void(bool&,int)> callback;

	AudioManager& audioManager;
	sf::SoundBuffer correctClickBuffer;
	sf::SoundBuffer wrongClickBuffer;
	sf::SoundBuffer attackBuffer;
	sf::SoundBuffer criticalHitBuffer;
	sf::SoundBuffer receibeDamageBuffer;
	sf::SoundBuffer receibeHighDamageBuffer;
	sf::SoundBuffer winBuffer;
	sf::SoundBuffer loseBuffer;
};

