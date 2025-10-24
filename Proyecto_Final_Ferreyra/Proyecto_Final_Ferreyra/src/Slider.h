#pragma once
#include "SFML/Graphics.hpp"
#include "Bar.h"
#include <functional>
class Slider
{
public:
	Slider(std::function<void(float)> function);
	~Slider();
	
	void Drag(sf::Vector2i mousePosition);
	bool GetIsDragging() const;
	void SetIsDragging(bool value);
	sf::CircleShape* GetCircleShape() const;
	sf::RectangleShape* GetSliderBar() const;
	sf::RectangleShape* GetSliderBackground() const;

private:
	float sliderX = 100.f;
	float sliderY = 100.f;
	float sliderWidth = 6.f;
	float sliderHeight = 400.f;
	float value = 0.0f;
	sf::CircleShape* handle;
	sf::RectangleShape* sliderBackground;
	sf::RectangleShape* sliderBar;

	bool isDragging = false;
	std::function<void(float)> callback;
};

