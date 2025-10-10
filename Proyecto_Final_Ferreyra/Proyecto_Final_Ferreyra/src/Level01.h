#pragma once
#include "Map.h"
class Level01 : public Map
{
public:
	Level01(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& audioManager);
	~Level01() override;

	void Initialize() override;
	bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable);
	void PlayBackgroundMusic() override;
	Asset* goToWoods;
	Map* nextMap;

private: 
	void LoadNextMap();
	void StartDialog();
};

