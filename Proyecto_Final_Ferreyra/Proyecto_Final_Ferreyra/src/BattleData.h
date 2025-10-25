#pragma once
#include <SFML/Graphics.hpp>
struct BattleData
{
	BattleData() = default;
	BattleData(sf::Sprite* sprite, float limitCounter,int damage, int health, int inputs, int id, int metals)
		: enemySprite(sprite), limitCounter(limitCounter), enemyDamage(damage), enemyHealth(health), totalInputs(inputs), enemyID(id),metalsAmount(metals) { }
	sf::Sprite* enemySprite;
	float limitCounter;
	int enemyDamage;
	int enemyHealth;
	int totalInputs;
	int enemyID;
	int metalsAmount;
};

