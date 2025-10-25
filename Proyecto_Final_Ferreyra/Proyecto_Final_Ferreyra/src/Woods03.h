#pragma once
#include "Map.h"
class Woods03 :	public Map
{
public:
	Woods03(const std::string& filePath, ManagersData& managersData, std::function<void()> onEnd);
	~Woods03() override;

	void Initialize() override;
	//bool CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable) override;
	void PlayBackgroundMusic() override;
	Asset* goToWoods02;

	Asset* castleEntranceDoor;
	Asset* castleEntranceDoorCollision;

private:
	void CastleEntranceDoorInteraction();
	void EndGame();
	std::function<void()> onEndGame;
};

