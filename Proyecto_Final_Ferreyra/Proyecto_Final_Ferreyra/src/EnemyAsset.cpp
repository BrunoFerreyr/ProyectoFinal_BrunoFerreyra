#include "EnemyAsset.h"
EnemyAsset::EnemyAsset(AssetData assetData, BattleData data, std::function<void()> func)
	: TriggerAsset(assetData, std::move(func)), enemyBattleData(data)
{
	enemyBattleData.enemySprite = this->GetSprite();
}
EnemyAsset::~EnemyAsset()
{
	enemyBattleData.enemySprite = nullptr;
}