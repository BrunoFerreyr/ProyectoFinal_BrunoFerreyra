#pragma once
#include "Map.h"
class Level02 : public Map
{
public:
	Level02(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& audioManager);
	~Level02() override;

	void Initialize() override;
	void PlayBackgroundMusic() override;
	Asset* goToHouse;
	Asset* goToCave;
	Asset* goToWoods01;
	Asset* enemyBat = nullptr;
	
private:
	void LoadHouse();
	void LoadCave();
	void LoadWoods01();
	void LoadBattle(int enemyLife, Asset* enemy);
};

