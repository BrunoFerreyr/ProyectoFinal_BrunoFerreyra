#pragma once
#include <functional>
#include "Asset.h"

class TriggerAsset : public Asset
{
public:
	TriggerAsset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision, std::function<void()> func);
	~TriggerAsset() override;

	bool SetCollision(bool collision);
	bool GetCollision() const;
	void OnTriggerEnter();
	void SetOnTriggerEnter(std::function<void()> func);
	int enemyLife;

private:
	std::function<void()> onTriggerEnterFunc;
	std::function<void(int&, Asset*)> onBattleFunc;
};

