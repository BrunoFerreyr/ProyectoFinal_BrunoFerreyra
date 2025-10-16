#include "CollectablesUI.h"

CollectablesUI::CollectablesUI(ResourceManager& resourceManager, MissionsManager* missions)
{
	metalsIcon = new Asset(&resourceManager.GetTexture("../textures/ui/metalsIcon.png", false, sf::IntRect()), sf::Vector2f({ 50.0f,50.0f }), sf::IntRect({ 0,0 }, { 32,32 }), false);
	woodsKeyIcon = new Asset(&resourceManager.GetTexture("../textures/ui/metalsIcon.png", false, sf::IntRect()), sf::Vector2f({ 50.0f,50.0f }), sf::IntRect({ 0,0 }, { 32,32 }), false);
	castleEntranceKeyIcon = new Asset(&resourceManager.GetTexture("../textures/ui/metalsIcon.png", false, sf::IntRect()), sf::Vector2f({ 50.0f,50.0f }), sf::IntRect({ 0,0 }, { 32,32 }), false);
	castleKeyIcon = new Asset(&resourceManager.GetTexture("../textures/ui/metalsIcon.png", false, sf::IntRect()), sf::Vector2f({ 50.0f,50.0f }), sf::IntRect({ 0,0 }, { 32,32 }), false);
	
	font = resourceManager.GetFont("../fonts/dogicapixel.ttf");
	metalsText = new sf::Text(font);
	metalsText->setCharacterSize(24);
	metalsText->setFillColor(sf::Color::White);
	metalsText->setPosition({ 90.0f,  50.0f });
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
	window.draw(*woodsKeyIcon->GetSprite());
	window.draw(*castleEntranceKeyIcon->GetSprite());
	window.draw(*castleKeyIcon->GetSprite());
	window.draw(*metalsText);
}
void CollectablesUI::SetMetalAmount(int incrementAmount)
{
	metalsAmount += incrementAmount;

	metalsText->setString("x " + std::to_string(metalsAmount));
}