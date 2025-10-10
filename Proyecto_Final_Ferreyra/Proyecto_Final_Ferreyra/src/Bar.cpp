#include "Bar.h"
Bar::Bar(sf::Texture* texture, sf::IntRect area, int width) : width(width)
{
	bar = new Asset(texture, { 0.0f,0.0f }, area, false);
}
Bar::~Bar()
{
	delete bar;
}
void Bar::SetPercentage(int percentage)
{
	std::cout << "SetPercentage: " << percentage << std::endl;
	if (percentage < 0.0f) percentage = 0.0f;
	if (percentage > 100.0f) percentage = 100.0f;
	sf::IntRect rect = bar->GetSprite()->getTextureRect();
	//rect.size.x = (percentage * rect.size.x) / 100;
	rect.size.x = (percentage * width) / 100;
	bar->GetSprite()->setTextureRect(rect);
}

Asset* Bar::GetBar() const 
{ 
	return bar; 
}