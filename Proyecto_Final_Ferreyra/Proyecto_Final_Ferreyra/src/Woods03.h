#pragma once
#include "Map.h"
class Woods03 :	public Map
{
public:
	Woods03(const std::string& filePath, ManagersData& managersData, std::function<void()> onEnd, std::function<void()> resetPositions);
	~Woods03() override;

	void Initialize() override;
	void PlayBackgroundMusic() override;
	Asset* goToWoods02;

	Asset* castleEntranceDoor;
	Asset* castleEntranceDoorCollision;

private:
	void CastleEntranceDoorInteraction();
	void EndGame();
	std::function<void()> onEndGame;
};

