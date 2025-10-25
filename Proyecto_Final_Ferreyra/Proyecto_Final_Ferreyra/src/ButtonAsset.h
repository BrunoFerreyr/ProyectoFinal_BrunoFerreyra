#pragma once
#include <functional>
#include <SFML/Audio.hpp>
#include "Asset.h"
class ButtonAsset : public Asset
{
public:
	ButtonAsset(AssetData assetData, sf::Font& font, const std::string& buttonName);
	virtual ~ButtonAsset() override;

	sf::Text* GetText();
	sf::SoundBuffer& GetBuffer();

private:
	sf::Text* buttonText;
	sf::SoundBuffer clickBuffer;
};

