#pragma once
#include "Map.h"
class Level02 : public Map
{
public:
	Level02(const std::string& filePath, ManagersData& managersData, std::function<void()> resetPositions);
	~Level02() override;

	void Initialize() override;
	void PlayBackgroundMusic() override;
	
private:
	void WoodsDoorInteraction();

	Asset* goToHouse;
	Asset* goToCave;
	Asset* goToWoods01;
	Asset* woodsDoor;
	Asset* woodsDoorCollision;
};

