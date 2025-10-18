#pragma once
#include "Map.h"
class Woods02 : public Map
{
public:
	Woods02(const std::string& filePath, ManagersData& managersData);
	~Woods02() override;

	void Initialize() override;
	//bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable) override;
	void PlayBackgroundMusic() override;
	Asset* goToWoods01;
	Asset* goToWoods03;
};

