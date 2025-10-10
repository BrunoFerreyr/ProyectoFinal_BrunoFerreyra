#pragma once
#include <SFML/Graphics.hpp>
#include "Asset.h"
#include <iostream>
class Bar
{
public:
	Bar(sf::Texture* texture,sf::IntRect area, int width);
	~Bar();
	void SetPercentage(int percentage);

	int width;
	Asset* bar;
	Asset* GetBar() const;
};

