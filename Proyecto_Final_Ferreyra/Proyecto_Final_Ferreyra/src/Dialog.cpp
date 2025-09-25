#include "Dialog.h"

Dialog::Dialog(ResourceManager& resourceManager)
{
	font = resourceManager.GetFont("../fonts/dogicapixel.ttf");
	if (font.getInfo().family.empty())
	{
		std::cerr << "Failed to load font for dialog." << std::endl;
	}
	
	//this->player = player;

	active = false;
	
	dialogs.push_back("Hello there, traveler! Welcome to our humble village.");
	dialogs.push_back("Feel free to explore and talk to the locals.");
	dialogs.push_back("If you need any help, don't hesitate to ask!");
	dialogs.push_back("Safe travels on your journey ahead!");
}
Dialog::~Dialog()
{
}
void Dialog::Start(const int startIndex,const int finishIndex)
{
	active = true;
	//player->SetInDialog(true);
	currentDialogIndex = startIndex;
	finishDialogIndex = finishIndex;
}
void Dialog::NextDialog()
{
	if (active)
	{
		if (currentDialogIndex < finishDialogIndex)
		{
			currentDialogIndex++;
		}
		else
		{
			active = false;
			currentDialogIndex = 0;
			//player->SetInDialog(false);
		}
	}
}
void Dialog::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		sf::RectangleShape background;
		background.setSize({ static_cast<float>(window.getSize().x) - 100.0f, 150.0f });
		background.setFillColor(sf::Color(0, 0, 0, 150));
		background.setPosition(sf::Vector2(50.0f, window.getSize().y - 200.0f));
		window.draw(background);

		sf::Text text = sf::Text(font);
		text.setFont(font);
		text.setString(dialogs[currentDialogIndex]);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2(70.0f, window.getSize().y - 180.0f));
		window.draw(text);
	}
}
bool Dialog::IsActive() const
{
	return active;
}