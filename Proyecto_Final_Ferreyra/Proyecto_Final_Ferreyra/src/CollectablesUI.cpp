#include "CollectablesUI.h"

CollectablesUI::CollectablesUI(ResourceManager& resourceManager, MissionsManager& missions) : missionManager(missions)
{
	metalsIcon = new Asset({ &resourceManager.GetTexture("../textures/ui/metals.png", false, sf::IntRect()), sf::Vector2f({100.0f,50.0f}), sf::IntRect({0,0}, {32,32}), false, true, nullptr });
	woodsKeyIcon = new Asset({ &resourceManager.GetTexture("../textures/ui/woodsKey.png", false, sf::IntRect()), sf::Vector2f({ 300.0f,50.0f }), sf::IntRect({ 0,0 }, { 10,28 }), false, true, nullptr});
	castleEntranceKeyIcon = new Asset({ &resourceManager.GetTexture("../textures/ui/castleEntranceKey.png", false, sf::IntRect()), sf::Vector2f({ 400.0f,50.0f }), sf::IntRect({ 0,0 }, { 14,27 }), false, true, nullptr });
	castleKeyIcon = new Asset({ &resourceManager.GetTexture("../textures/ui/castleKey.png", false, sf::IntRect()), sf::Vector2f({ 500.0f,50.0f }), sf::IntRect({ 0,0 }, { 10,28 }), false, true, nullptr });
	
	font = resourceManager.GetFont("../fonts/dogicapixel.ttf");
	metalsText = new sf::Text(font);
	metalsText->setString(" 0");	
	metalsText->setCharacterSize(20);
	metalsText->setFillColor(sf::Color::White);
	metalsText->setPosition({ 130.0f,  55.0f });
}
CollectablesUI::~CollectablesUI()
{
	delete metalsIcon;
	delete woodsKeyIcon;
	delete castleEntranceKeyIcon;
	delete castleKeyIcon;
	delete metalsText;
}
void CollectablesUI::Draw(sf::RenderWindow& window)
{
	window.draw(*metalsIcon->GetSprite());
	if (missionManager.HasWoodsKey()) 
	{
		window.draw(*woodsKeyIcon->GetSprite());
	}
	if (missionManager.HasCastleEntranceKey())
	{
		window.draw(*castleEntranceKeyIcon->GetSprite());
	}
	if (missionManager.HasCastleKey())
	{
		window.draw(*castleKeyIcon->GetSprite());
	}
	window.draw(*metalsText);
}
void CollectablesUI::SetMetalAmount(int incrementAmount)
{
	metalsAmount += incrementAmount;

	metalsText->setString(" " + std::to_string(metalsAmount));
}
int CollectablesUI::GetMetalAmount() const
{
	return metalsAmount;
}