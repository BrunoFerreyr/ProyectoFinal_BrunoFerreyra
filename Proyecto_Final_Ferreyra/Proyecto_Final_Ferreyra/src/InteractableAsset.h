#pragma once
#include "Asset.h"
#include <functional>

class InteractableAsset :public Asset
{
public:
	InteractableAsset(AssetData assetData, std::function<void()> function);
	~InteractableAsset() override;

	void SetOnTriggerInteract(std::function<void()> function);
	void IdleAnimation(float deltaTime);
	void Interact();

private:
	std::function<void()> onInteractFunction;
	bool haveIdleAnimation = false;
};

