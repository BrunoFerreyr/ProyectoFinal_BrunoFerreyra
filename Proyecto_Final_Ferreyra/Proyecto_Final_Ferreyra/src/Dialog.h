#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ResourceManager.h"

class Dialog
{
public:
	Dialog(ResourceManager& resourceManager);
	~Dialog();
	void Start(const int startIndex, const int finishIndex);
	void NextDialog();
	void Draw(sf::RenderWindow& window);
	bool IsActive() const;
private:
	bool active;
	std::vector<std::string> dialogs;
	int currentDialogIndex;
	int finishDialogIndex;
	sf::Font font;
};