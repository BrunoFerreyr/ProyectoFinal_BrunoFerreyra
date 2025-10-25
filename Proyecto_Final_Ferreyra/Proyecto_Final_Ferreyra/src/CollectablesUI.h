#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "MissionsManager.h"
#include "Asset.h"
class CollectablesUI
{
public:
	CollectablesUI(ResourceManager& resourceManager, MissionsManager& missions);
	~CollectablesUI();

	void Draw(sf::RenderWindow& window);
	void AddMetalAmount(int incrementAmount);
	int GetMetalAmount() const;

private:
	Asset* castleKeyIcon;
	Asset* castleEntranceKeyIcon;
	Asset* woodsKeyIcon;
	Asset* metalsIcon;
	MissionsManager& missionManager;
	sf::Text* metalsText;
	sf::Font font;
	int metalsAmount = 0;
};

