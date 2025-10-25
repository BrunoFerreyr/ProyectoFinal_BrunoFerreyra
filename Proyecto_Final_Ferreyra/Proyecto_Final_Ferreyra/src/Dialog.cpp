#include "Dialog.h"

Dialog::Dialog(ResourceManager& resourceManager)
{
	font = resourceManager.GetFont("../fonts/dogicapixel.ttf");
	if (font.getInfo().family.empty())
	{
		std::cerr << "Failed to load font for dialog." << std::endl;
	}
	
	active = false;

	dialogFile.open("../files/dialogs.txt");
	std::string dialogLine = "";
	std::string numberLine = "";
	std::string fullLine = "";
	while (std::getline(dialogFile, fullLine))
	{
		size_t delimiterPos = fullLine.find('/');
		if (delimiterPos != std::string::npos)
		{
			int dialogIndex = std::stoi(fullLine.substr(0, delimiterPos));
			dialogLine = fullLine.substr(delimiterPos + 1);

			size_t pos = 0;
			while ((pos = dialogLine.find("\\n", pos)) != std::string::npos) {
				dialogLine.replace(pos, 2, "\n");
				pos += 1;
			}

			dialogs.emplace(dialogIndex, dialogLine);
			std::cout << "Loaded dialog " << dialogIndex << ": " << dialogLine << std::endl;
		}		
	}
	dialogFile.close();		

	text = new sf::Text(font);
	text->setFont(font);
	text->setCharacterSize(24);
	text->setLineSpacing(1.5f);
	text->setFillColor(sf::Color::White);
	text->setPosition(sf::Vector2(70.0f, 720.0f - 180.0f));

	background = sf::RectangleShape({ 1280.0f - 100.0f, 150.0f });
	background.setFillColor(sf::Color(0, 0, 0, 150));
	background.setPosition(sf::Vector2f(50.0f, 720.0f - 200.0f));
}
Dialog::~Dialog()
{
	delete text;
	text = nullptr;
}

void Dialog::Start(const int startIndex,const int finishIndex, std::function<void()> callback)
{
	active = true;
	currentDialogIndex = startIndex;
	finishDialogIndex = finishIndex;
	text->setString(dialogs[currentDialogIndex]);
	if (callback != nullptr)
	{
		this->callback = callback;
	}	
}

void Dialog::Draw(sf::RenderWindow& window)
{
	if (active)
	{		
		window.draw(background);		
		window.draw(*text);
	}
}

void Dialog::NextDialog()
{
	if (active)
	{
		if (currentDialogIndex < finishDialogIndex)
		{
			currentDialogIndex++;
			text->setString(dialogs[currentDialogIndex]);
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
		}
	}
}

bool Dialog::IsActive() const
{
	return active;
}