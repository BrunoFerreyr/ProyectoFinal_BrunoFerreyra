#pragma once
#include <functional>
#include "Asset.h"

class TriggerAsset : public Asset
{
public:
	TriggerAsset(AssetData assetData, std::function<void()> func);
	virtual ~TriggerAsset() override;

	bool SetCollision(bool collision);
	bool GetCollision() const;
	void OnTriggerEnter();
	void SetOnTriggerEnter(std::function<void()> func);

private:
	std::function<void()> onTriggerEnterFunc;
};

