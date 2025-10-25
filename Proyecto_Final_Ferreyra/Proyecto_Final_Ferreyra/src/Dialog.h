#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "ResourceManager.h"

class Dialog
{
public:
	Dialog(ResourceManager& resourceManager);
	~Dialog();

	void Start(const int startIndex, const int finishIndex, std::function<void()> callback);
	void NextDialog();
	void Draw(sf::RenderWindow& window);
	bool IsActive() const;

private:
	bool active;
	std::map<int,std::string> dialogs;
	int currentDialogIndex;
	int finishDialogIndex;
	sf::Font font;
	std::function<void()> callback;
	std::ifstream dialogFile;
};