#pragma once
#include "SFML/Graphics.hpp"
#include "Bar.h"
#include "ResourceManager.h"
#include <functional>
class Slider
{
public:
	Slider(ResourceManager& resourceManager, std::string path, sf::Vector2f barPosition, std::function<void(float)> function);
	~Slider();
	
	void Drag(sf::Vector2i mousePosition);
	bool GetIsDragging() const;
	void SetIsDragging(bool value);
	sf::CircleShape* GetCircleShape() const;
	sf::Sprite* GetSliderBar() const;
	sf::Sprite* GetSliderBackground() const;

private:
	float sliderX = 150.f;
	float sliderY = 300.f;
	int sliderWidth = 28;
	int sliderHeight = 159;
	int backgroundWidth = 40;
	int backgroundHeight = 200;
	float value = 0.0f;
	float valueMultiplier = 100.0f;
	sf::CircleShape* handle;
	Asset* sliderBackground;
	Asset* sliderBar;

	bool isDragging = false;
	std::function<void(float)> callback;
};

