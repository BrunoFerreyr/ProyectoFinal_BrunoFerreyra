#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Map.h"
#include "Dialog.h"
#include "PlayerAnimations.h"
#include "PlayerState.h"
class Player
{
private:
	sf::Sprite* sprite;
	Map* currentMap;
	float speed = 2;
	sf::Vector2f direction;
	sf::Vector2f moveDirection;

	bool isInteracting;
	Dialog* dialog;
	PlayerAnimations* animations;
public:
	Player(const std::string& path, const sf::Vector2i& spriteSheetSize, ResourceManager& resourceManager, Dialog* dialog);
	~Player();

	void Input();
	void Update(float deltaTime);
	void MovementInput();
	void Movement(float deltaTime);
	void Animation(float deltaTime); 
	void Interact();
	void Draw(sf::RenderWindow& window);
	sf::FloatRect GetBounds();
	void SetCurrentMap(Map* map, sf::Vector2f position);

	void HandleEvents(const sf::Event& event);
};

