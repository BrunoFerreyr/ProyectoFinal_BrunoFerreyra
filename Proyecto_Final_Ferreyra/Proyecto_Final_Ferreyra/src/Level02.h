#pragma once
#include "Map.h"
class Level02 : public Map
{
public:
	Level02(const std::string& filePath, ManagersData& managersData);
	~Level02() override;

	void Initialize() override;
	void PlayBackgroundMusic() override;
	Asset* goToHouse;
	Asset* goToCave;
	Asset* goToWoods01;
	Asset* woodsDoor;

private:
	void WoodsDoorInteraction();
};

