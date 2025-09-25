#pragma once
#include <SFML/Graphics.hpp>

class Interactable
{
public:
	Interactable();
	~Interactable();
	virtual void Interact() = 0;
	sf::Sprite* sprite;

};