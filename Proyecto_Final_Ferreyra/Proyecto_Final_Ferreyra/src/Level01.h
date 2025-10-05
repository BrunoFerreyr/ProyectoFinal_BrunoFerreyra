#pragma once
#include "Map.h"
class Level01 : public Map
{
public:
	Level01(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& audioManager);
	~Level01() override;
	bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable);

	Asset* goToWoods;
	Map* nextMap;
	void PlayBackgroundMusic() override;
private: 
	void LoadNextMap();
	void StartDialog();
};

