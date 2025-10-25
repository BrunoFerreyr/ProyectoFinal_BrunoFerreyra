#include "Slider.h"
Slider::Slider(ResourceManager& resourceManager, std::string path, sf::Vector2f barPosition, std::function<void(float)> function)
{
	sliderX = barPosition.x;
	sliderY = barPosition.y;

	sliderBackground = new Asset({ &resourceManager.GetTexture(path, false, sf::IntRect()), sf::Vector2f{sliderX, sliderY}, sf::IntRect({0,0}, {backgroundWidth, backgroundHeight}), false, true, nullptr });
	sliderBar = new Asset({ &resourceManager.GetTexture("../textures/menu/musicBar.png", false, sf::IntRect()), { sliderX, sliderY }, sf::IntRect({ 0, 0 }, { sliderWidth, sliderHeight }), false, true, nullptr });
    value = 0.5f;

    sf::Vector2f spritePos = sliderBar->GetSprite()->getPosition();
    sliderBar->GetSprite()->setOrigin({ sliderWidth / 2.f, 0 });
    sliderBar->GetSprite()->setPosition({sliderX + (backgroundWidth * 0.5f), sliderY + sliderHeight + 35});
    
	sliderBar->GetSprite()->setRotation(sf::degrees(180.f));
	sliderY = sliderBar->GetSprite()->getPosition().y - sliderHeight;

    sf::IntRect rect = sliderBar->GetSprite()->getTextureRect();
    rect.size.y = (50 * sliderHeight) / 100;
    sliderBar->GetSprite()->setTextureRect(rect);

    float circleRadius = 10.f;
    handle = new sf::CircleShape(circleRadius);
    handle->setFillColor(sf::Color::Red);
    handle->setOrigin({ circleRadius, circleRadius });
    handle->setPosition({ sliderX + (backgroundWidth * 0.5f) , sliderY + (sliderHeight * value) });

    callback = function;
	callback(value);
}
Slider::~Slider()
{
	delete handle;
	delete sliderBackground;
	delete sliderBar;
}
void Slider::Drag(sf::Vector2i mousePosition)
{
    if (isDragging) 
    {
        float newY = static_cast<float>(mousePosition.y);

        if (newY < sliderY) newY = sliderY;
        if (newY > sliderY + sliderHeight) newY = sliderY + sliderHeight;

		float x = sliderBar->GetSprite()->getPosition().x;
        handle->setPosition({ x, newY});

        float relative = (newY - sliderY) / sliderHeight;
        if (relative < 0.0f)
        { 
            relative = 0.0f;
        }
        if (relative > 1.0f)
        { 
            relative = 1.0f;
        }
        value = 1.0f - relative;

        sf::IntRect rect = sliderBar->GetSprite()->getTextureRect();
        rect.size.y = ((value * valueMultiplier) * sliderHeight) / 100;
        sliderBar->GetSprite()->setTextureRect(rect);

        if (callback) 
        {
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
sf::Sprite* Slider::GetSliderBar() const
{
    return sliderBar->GetSprite();
}
sf::Sprite* Slider::GetSliderBackground() const 
{
	return sliderBackground->GetSprite();
}
