#pragma once
#include "Asset.h"
#include <functional>

class InteractableAsset :public Asset
{
public:
	InteractableAsset(AssetData assetData, std::function<void()> func);
	~InteractableAsset() override;

	void IdleAnimation(float deltaTime);
	void SetOnTriggerInteract(std::function<void()> func);
	void Interact();

private:
	std::function<void()> onInteractFunc;
	bool haveIdleAnimation = false;
};

