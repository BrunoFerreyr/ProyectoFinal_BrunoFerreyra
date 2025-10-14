#pragma once
#include "TriggerAsset.h"
#include "BattleData.h"
class EnemyAsset : public TriggerAsset
{
public:
	EnemyAsset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision, BattleData data, std::function<void()> func);
	~EnemyAsset() override;

	int enemyLife;
	BattleData enemyBattleData;
};

