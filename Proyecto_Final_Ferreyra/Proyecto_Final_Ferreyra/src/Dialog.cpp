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
	
	dialogs.push_back("Old lady: Hello there, traveler! Welcome to my lovely home. Whats your name?");
	dialogs.push_back("My name is Martial, where am i?");
	dialogs.push_back("For years we are having trouble with the machines, if you help me fighting with them...");
	dialogs.push_back("... and you give me 5 metals, i will give you more information");
	dialogs.push_back("Martial: Deal.");
	dialogs.push_back("Old lady: Thank you so much, here is the key to enter the woods.");

	dialogs.push_back("Old lady: Good luck with that!.");

	dialogs.push_back("Old lady: Oh, you are back! Did you bring the metals?");
	dialogs.push_back("Martial: Yes, here you go.");
	dialogs.push_back("Old lady: Wonderful! As promised, i will give you information.");
	dialogs.push_back("Old lady: You are on a digital world, this place was created long time ago, to get more information, you will need to go the castle, but it will be a long fight against the machines.");
	dialogs.push_back("Old lady: The machines were created by a king, he wanted to create an army to defend his castle.");
	dialogs.push_back("Old lady: But something went wrong, the machines turned against him and destroyed everything.");
	dialogs.push_back("Old lady: If you want to enter the castle, you will need to defeat the knight that guards the door.");
	dialogs.push_back("Old lady: Here is the key to enter the castle entrance.");
	dialogs.push_back("Martial: Thanks for all.");

	dialogs.push_back("Old lady: Take care of yourself, good luck on your journey");
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
			if(callback != nullptr)
			{
				callback();
				callback = nullptr;
			}
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