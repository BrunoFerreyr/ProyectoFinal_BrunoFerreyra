#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "ResourceManager.h"
#include "Asset.h"
#include "Bar.h"
class Battle
{
public:
	Battle(ResourceManager& resourceManager,int playerLife, int enemyLife, Asset* enemySprite, std::function<void(bool&,Asset*)> callback);
	~Battle();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void HandleEvents(const sf::Event& event);

private:
	void StartBattle();
	void EndBattle();
	
	void ShowKeys();
	void DoAction();

	//sf::Keyboard::Key charToKey(char keyChar) const;
	sf::Keyboard::Key GetCorrectKey() const;
	void UpdateStats();
	void PlayerWin();
	void PlayerLose();

	bool battleEnded = false;
	bool playerWins = false;
	bool battleActive = false;
	bool shouldTap = false;
	bool isAttacking = false;
	float counter = 0.0f;
	float limitCounter = 3.0f;
	float waitCounter = 0.0f;
	float waitLimit = 1.0f;
	Asset* playerSprite;
	Asset* enemySprite;
	Asset* playerLifeSprite;
	Asset* enemyLifeSprite;
	std::vector<sf::Keyboard::Key> correctKeys;
	std::vector<Asset*> keysAssets;
	std::vector<sf::Sprite*> keysSprites;
	//capaz crear un enum con Normal, Correct y Failed

	std::vector<char> keysChar;
	std::vector<char> allKeysChar;
	std::vector<sf::Keyboard::Key> allKeys;
	int totalPoints = 0;
	int keyPointValue = 4;
	int enemyDamage = 14;
	int inputIndex = 0;
	int totalInputs = 3;
	int playerHealth = 100;
	int enemyHealth = 100;
	sf::Font font;
	sf::Text* pointsText;
	sf::Text* playerText;
	sf::Text* enemyText;
	sf::Text* keysText;//DO Vector.
	sf::Text* roundText;
	Bar* timeBar;
	std::function<void(bool&,Asset*)> callback;
};

