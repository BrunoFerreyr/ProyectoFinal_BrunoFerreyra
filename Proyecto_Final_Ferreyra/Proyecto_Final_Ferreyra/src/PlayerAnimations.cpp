#include "PlayerAnimations.h"

PlayerAnimations::PlayerAnimations(sf::Texture& texture)
{
	this->texture = &texture;
	currentXValue = 0;
	animationTimer = 0.0f;
	area = sf::IntRect({ 0,0 }, { spriteWidth,spriteHeight });
}
PlayerAnimations::~PlayerAnimations()
{
}
void PlayerAnimations::Update(float deltaTime, sf::Vector2f& direction)
{
	switch (currentState)
	{
	case PlayerState::Idle:
		IdleAnimation(deltaTime, direction);
		break;
	case PlayerState::Walking:
		WalkingAnimation(deltaTime, direction);
		break;
	case PlayerState::Attacking:
		break;
	case PlayerState::TakingDamage:
		break;
	case PlayerState::Dying:
		break;
	default:
		break;
	}
}
void PlayerAnimations::IdleAnimation(float deltaTime, sf::Vector2f& direction)
{
	animationTimer += deltaTime;//tener dos direction, uno que se modficia con las teclas, y otro el que ya usa

	if (animationTimer >= animationSpeed)
	{
		if (direction == sf::Vector2f({ 1,0 })) // Right
			area = GetClip(spriteWidth, 96 * 3);
		else if (direction == sf::Vector2f({ -1,0 })) // Left
			area = GetClip(spriteWidth, 96);
		else if (direction == sf::Vector2f({ 0,-1 })) // Up
			area = GetClip(spriteWidth, 0);
		else if (direction == sf::Vector2f({ 0,1 })) // Down
			area = GetClip(spriteWidth, 96 * 2);

		animationTimer = 0.0f;
	}
}
void PlayerAnimations::WalkingAnimation(float deltaTime, sf::Vector2f& direction) 
{
	animationTimer += deltaTime;//tener dos direction, uno que se modficia con las teclas, y otro el que ya usa

	if (animationTimer >= animationSpeed)
	{	
		if (direction == sf::Vector2f({ 1,0 })) // Right
			area = GetClip(378 ,96 * 7);
		else if (direction == sf::Vector2f({ -1,0 })) // Left
			area = GetClip(378 ,96 * 5);
		else if (direction == sf::Vector2f({ 0,-1 })) // Up
			area = GetClip(378 ,96* 4);
		else if (direction == sf::Vector2f({ 0,1 })) // Down
		area = GetClip(378 ,96 * 6);

		animationTimer = 0.0f;
	}
}
sf::IntRect PlayerAnimations::GetClip(int xLimit, int yAnim)
{
	currentXValue += spriteWidth;
	if (currentXValue >= xLimit)
	{
		currentXValue = 0;
	}	

	return sf::IntRect({ currentXValue,yAnim }, { spriteWidth,spriteHeight });
}
void PlayerAnimations::SetState(PlayerState newState)
{
	currentState = newState;
}
sf::IntRect& PlayerAnimations::GetSprite()
{		 
	std::cout << "position " << area.position.x << " and y is = " << area.position.y << std::endl;
	std::cout << "scale " << area.size.x << " and y is = " << area.size.y << std::endl;	
	return area;
}