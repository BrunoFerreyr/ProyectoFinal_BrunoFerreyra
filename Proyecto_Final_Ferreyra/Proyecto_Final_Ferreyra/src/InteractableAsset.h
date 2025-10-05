#pragma once
#include "Asset.h"
#include <functional>

class InteractableAsset :public Asset
{
public:
	InteractableAsset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision, std::function<void()> func);
	~InteractableAsset() override;

	void IdleAnimation(float deltaTime);
	void SetOnTriggerInteract(std::function<void()> func);
	void Interact();

private:
	std::function<void()> onInteractFunc;
	bool haveIdleAnimation = false;
};

