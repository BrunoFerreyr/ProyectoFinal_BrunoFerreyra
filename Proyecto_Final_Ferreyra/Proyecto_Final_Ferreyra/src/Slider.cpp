#include "Slider.h"
Slider::Slider(std::function<void(float)> function)
{
    sliderBackground = new sf::RectangleShape(sf::Vector2f(sliderWidth, sliderHeight));
    sliderBackground->setPosition({ sliderX, sliderY });
    sliderBackground->setFillColor(sf::Color(150, 150, 150));

    float circleRadius = 10.f;
    handle = new sf::CircleShape(circleRadius);
    handle->setFillColor(sf::Color::Red);
    handle->setOrigin({ circleRadius, circleRadius });
    handle->setPosition({ sliderX + sliderWidth / 2.f , sliderY });

	sliderBar = new sf::RectangleShape(sf::Vector2f(sliderWidth, sliderHeight));
    sliderBar->setPosition({ sliderX, sliderY });
    sliderBar->setFillColor(sf::Color(150, 0, 150));

    sf::IntRect rect = sliderBar->getTextureRect();
    //rect.size.x = (percentage * rect.size.x) / 100;
    rect.size.y = (50 * sliderHeight) / 100;
    sliderBar->setTextureRect(rect);	
    
    callback = function;
	callback(0.5f);
}
Slider::~Slider()
{
	delete handle;
}
void Slider::Drag(sf::Vector2i mousePosition)
{
    if (isDragging) {
        float newY = static_cast<float>(mousePosition.y);

        if (newY < sliderY) newY = sliderY;
        if (newY > sliderY + sliderHeight) newY = sliderY + sliderHeight;

        handle->setPosition({ sliderX + (sliderWidth / 2.f), newY});

        float relative = (newY - sliderY) / sliderHeight;
        if (relative < 0.f) relative = 0.f;
        if (relative > 1.f) relative = 1.f;
        value = 1.0f - relative;

        sf::IntRect rect = sliderBar->getTextureRect();
        //rect.size.x = (percentage * rect.size.x) / 100;
        rect.size.y = ((value * 100) * sliderHeight) / 100;
        sliderBar->setTextureRect(rect);
        if (callback) {
            callback(value);
            
		}
    }
}
bool Slider::GetIsDragging() const
{
    return isDragging;
}
void Slider::SetIsDragging(bool value)
{
	isDragging = value;
}
sf::CircleShape* Slider::GetCircleShape() const
{
    return handle;
}
sf::RectangleShape* Slider::GetSliderBar() const
{
    return sliderBar;
}
sf::RectangleShape* Slider::GetSliderBackground() const 
{
	return sliderBackground;
}
