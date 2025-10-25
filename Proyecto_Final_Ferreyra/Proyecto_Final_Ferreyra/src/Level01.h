#pragma once
#include "Map.h"
class Level01 : public Map
{
public:
	Level01(const std::string& filePath, ManagersData& managersData);
	~Level01() override;

	void Initialize() override;
	void PlayBackgroundMusic() override;
	Asset* goToWoods;

private: 
	void StartDialog();

	sf::SoundBuffer earnKeyBuffer;
};

