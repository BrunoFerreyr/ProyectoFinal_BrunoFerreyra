#pragma once
#include "Map.h"
class Woods01 : public Map
{
public:
	Woods01(const std::string& filePath, ManagersData& managersData);
	~Woods01() override;

	void Initialize() override;
	//bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable) override;
	void PlayBackgroundMusic() override;
	Asset* goToCamp;
	Asset* goToWoods02;
};

