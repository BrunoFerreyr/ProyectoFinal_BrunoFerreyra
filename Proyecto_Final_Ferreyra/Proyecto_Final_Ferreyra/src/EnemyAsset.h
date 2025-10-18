#pragma once
#include "TriggerAsset.h"
#include "BattleData.h"
class EnemyAsset : public TriggerAsset
{
public:
	EnemyAsset(AssetData assetData, BattleData data, std::function<void()> func);
	~EnemyAsset() override;

	int enemyLife;
	BattleData enemyBattleData;
};

