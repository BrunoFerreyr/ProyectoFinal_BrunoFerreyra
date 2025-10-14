#pragma once
#include <SFML/Graphics.hpp>
struct BattleData
{
	BattleData() = default;
	BattleData(sf::Sprite* sprite, float limitCounter,int damage, int health, int inputs, int id)
		: enemySprite(sprite), limitCounter(limitCounter), enemyDamage(damage), enemyHealth(health), totalInputs(inputs), enemyID(id) { }
	sf::Sprite* enemySprite;
	float limitCounter;
	int enemyDamage;
	int enemyHealth;
	int totalInputs;
	int enemyID;
};

