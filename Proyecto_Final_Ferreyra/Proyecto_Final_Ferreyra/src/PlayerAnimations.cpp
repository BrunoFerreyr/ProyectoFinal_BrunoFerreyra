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
	texture = nullptr;
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
	default:
		break;
	}
}
void PlayerAnimations::SetState(PlayerState newState)
{
	currentState = newState;
}
sf::IntRect& PlayerAnimations::GetArea()
{
	return area;
}

void PlayerAnimations::IdleAnimation(float deltaTime, sf::Vector2f& direction)
{
	animationTimer += deltaTime;

	if (animationTimer >= animationSpeed)
	{
		if (direction == sf::Vector2f({ 1,0 }))
		{ 
			area = GetClip(spriteWidth, spriteHeight * 3);// Right
		}
		else if (direction == sf::Vector2f({ -1,0 }))
		{ 
			area = GetClip(spriteWidth, spriteHeight);// Left
		}
		else if (direction == sf::Vector2f({ 0,-1 }))
		{ 
			area = GetClip(spriteWidth, 0);// Up
		}
		else if (direction == sf::Vector2f({ 0,1 }))
		{ 
			area = GetClip(spriteWidth, spriteHeight * 2);// Down
		}
		animationTimer = 0.0f;
	}
}
void PlayerAnimations::WalkingAnimation(float deltaTime, sf::Vector2f& direction) 
{
	animationTimer += deltaTime;

	if (animationTimer >= animationSpeed)
	{	
		if (direction == sf::Vector2f({ 1,0 })) 
		{
			area = GetClip(378, spriteHeight * 7);// Right
		}
		else if (direction == sf::Vector2f({ -1,0 }))
		{ 
			area = GetClip(378 , spriteHeight * 5);// Left
		}
		else if (direction == sf::Vector2f({ 0,-1 }))
		{ 
			area = GetClip(378 , spriteHeight * 4);// Up
		}
		else if (direction == sf::Vector2f({ 0,1 }))
		{ 
			area = GetClip(378 , spriteHeight * 6);// Down
		}

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
