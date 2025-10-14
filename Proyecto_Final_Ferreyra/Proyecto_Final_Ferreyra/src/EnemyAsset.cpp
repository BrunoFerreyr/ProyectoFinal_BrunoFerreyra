#include "EnemyAsset.h"
EnemyAsset::EnemyAsset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision, BattleData data, std::function<void()> func)
	: TriggerAsset(texture, pos, size, collision, std::move(func)), enemyBattleData(data)
{
	enemyBattleData.enemySprite = this->GetSprite();
}
EnemyAsset::~EnemyAsset()
{
}