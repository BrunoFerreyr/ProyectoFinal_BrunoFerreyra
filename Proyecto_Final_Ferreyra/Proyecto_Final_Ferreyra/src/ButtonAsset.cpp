#include "ButtonAsset.h"
ButtonAsset::ButtonAsset(AssetData assetData, sf::Font& font,const std::string& buttonName)
	: Asset(assetData)
{
	buttonText = new sf::Text(font,buttonName,24);	
	buttonText->setFillColor(sf::Color::Black); 
	
	sf::FloatRect textBounds = buttonText->getLocalBounds();
	buttonText->setOrigin({textBounds.size.x * 0.5f,textBounds.size.y *0.5f });
	buttonText->setPosition({assetData.position.x + (assetData.size.size.x * 0.5f) ,assetData.position.y + (assetData.size.size.y * 0.5f)});

	clickBuffer.loadFromFile("../audios/sfx/buttonPress.ogg");
}
ButtonAsset::~ButtonAsset()
{
	delete buttonText;
}

sf::Text* ButtonAsset::GetText()
{
	return buttonText;
}
sf::SoundBuffer& ButtonAsset::GetBuffer()
{
	return clickBuffer;
}