#pragma once
#include <functional>
#include <SFML/Audio.hpp>
#include "Asset.h"
class ButtonAsset : public Asset
{
public:
	ButtonAsset(AssetData assetData, sf::Font& font, const std::string& buttonName, std::function<void()> func);
	virtual ~ButtonAsset() override;

	void OnClickEvent();
	sf::Text* GetText();
	sf::SoundBuffer& GetBuffer();

private:
	std::function<void()> onClickEvent;
	sf::Text* buttonText;

	sf::SoundBuffer clickBuffer;
};

