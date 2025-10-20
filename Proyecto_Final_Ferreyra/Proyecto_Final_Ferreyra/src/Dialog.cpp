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
	
	dialogs.emplace(0,"Old lady: Hello there, traveler! Welcome to my lovely home. Whats your name?");
	dialogs.emplace(1,"My name is Martial, where am i?");
	dialogs.emplace(2,"For years we are having trouble with the machines, if you help me fighting with them...");
	dialogs.emplace(3,"... and you give me 5 metals, i will give you more information");
	dialogs.emplace(4,"Martial: Deal.");
	dialogs.emplace(5,"Old lady: Thank you so much, here is the key to enter the woods.");

	dialogs.emplace(6,"Old lady: Good luck with that!.");

	dialogs.emplace(7,"Old lady: Oh, you are back! Did you bring the metals?");
	dialogs.emplace(8,"Martial: Yes, here you go.");
	dialogs.emplace(9,"Old lady: Wonderful! As promised, i will give you information.");
	dialogs.emplace(10,"Old lady: You are on a digital world, this place was created long time ago, to get more information, you will need to go the castle, but it will be a long fight against the machines.");
	dialogs.emplace(11,"Old lady: The machines were created by a king, he wanted to create an army to defend his castle.");
	dialogs.emplace(12,"Old lady: But something went wrong, the machines turned against him and destroyed everything.");
	dialogs.emplace(13,"Old lady: If you want to enter the castle, you will need to defeat the knight that guards the door.");
	dialogs.emplace(14,"Old lady: Here is the key to enter the castle entrance.");
	dialogs.emplace(15,"Martial: Thanks for all.");

	dialogs.emplace(16,"Old lady: Take care of yourself, good luck on your journey");

	dialogs.emplace(100,"You need the woods key to pass!");
	dialogs.emplace(101, "You need the castle entrance key to pass!");
}
Dialog::~Dialog()
{
}
void Dialog::Start(const int startIndex,const int finishIndex, std::function<void()> callback)
{
	active = true;
	//player->SetInDialog(true);
	currentDialogIndex = startIndex;
	finishDialogIndex = finishIndex;
	if (callback != nullptr)
	{
		this->callback = callback;
	}	
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