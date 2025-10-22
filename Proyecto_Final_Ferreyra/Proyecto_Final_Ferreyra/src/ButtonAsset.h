#pragma once
#include <functional>
#include "Asset.h"
class ButtonAsset : public Asset
{
public:
	ButtonAsset(AssetData assetData, sf::Font& font, const std::string& buttonName, std::function<void()> func);
	virtual ~ButtonAsset() override;

	void OnClickEvent();
	sf::Text* GetText();
	//int enemyLife;

private:
	std::function<void()> onClickEvent;
	sf::Text* buttonText;
};

