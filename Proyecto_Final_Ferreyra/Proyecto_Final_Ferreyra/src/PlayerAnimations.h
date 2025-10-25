#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerState.h"
class PlayerAnimations
{
public:
	PlayerAnimations(sf::Texture& texture);
	~PlayerAnimations();

	void Update(float deltaTime, sf::Vector2f& direction);
	void SetState(PlayerState newState);
	sf::IntRect& GetArea();

private:
	void IdleAnimation(float deltaTime, sf::Vector2f& direction);
	void WalkingAnimation(float deltaTime, sf::Vector2f& direction);
	sf::IntRect GetClip(int yAnim, int xLimit);

	sf::Texture* texture;
	sf::IntRect area;
	int currentXValue;
	int spriteWidth = 63;
	int spriteHeight = 96;
	float animationTimer;
	float animationSpeed = 0.1f; 
	PlayerState currentState = PlayerState::Walking;
	
};

