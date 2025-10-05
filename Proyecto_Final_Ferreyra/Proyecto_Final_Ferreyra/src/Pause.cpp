#include "Pause.h"
Pause::Pause(ResourceManager& resources, sf::RenderWindow& window, Scene*& currentScene, MainMenu*& mainMenu) :
	currentScene(currentScene), mainMenu(mainMenu), window(window)
{
	this->currentScene = currentScene;
	this->mainMenu = mainMenu;

	/*std::string pauseBackgroundPath = "../textures/pause/pausebackground.png";
	sf::IntRect pauseBackgroundArea({ 0,0 }, { 1280, 720 });
	sf::Texture& pauseBackgroundTexture = resources.GetTexture(pauseBackgroundPath, false, pauseBackgroundArea);
	pauseBackground = new sf::Sprite(pauseBackgroundTexture);
	pauseBackground->setPosition({ 1280 * 0.5f, 720 * 0.5f });*/
	
	sf::Texture& pauseButtonTexture = resources.GetTexture("../textures/continueButton.png", false, sf::IntRect({ 0,0 }, { 300, 100 }));
	continueButton = new sf::Sprite(pauseButtonTexture);
	continueButton->setPosition({ 640 - 150, 250 });

	sf::Texture& mainMenuButtonTexture = resources.GetTexture("../textures/mainmenuButton.png", false, sf::IntRect({ 0,0 }, { 300, 100 }));
	mainMenuButton = new sf::Sprite(mainMenuButtonTexture);
	mainMenuButton->setPosition({ 640 - 150, 400 });

	gamePaused = false;
}

Pause::~Pause() {}

void Pause::Input() {}

void Pause::Draw()
{
	if (!gamePaused) return;

	//window.draw(*pauseBackground);
	window.draw(*continueButton);
	window.draw(*mainMenuButton);

}

void Pause::HandleEvents(const sf::Event& event)
{
	if (const auto* key = event.getIf<sf::Event::KeyPressed>()) 
	{
		if (key->scancode == sf::Keyboard::Scancode::P) 
		{

			if (gamePaused) 
			{
				UnpauseGame();
			}
			else 
			{
				PauseGame();
			}
		}
	}

	if (!gamePaused) return;


	if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouse->button == sf::Mouse::Button::Left)
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			if (continueButton->getGlobalBounds().contains(worldPos))
			{
				UnpauseGame();
			}

			if (mainMenuButton->getGlobalBounds().contains(worldPos))
			{
				UnpauseGame();
				currentScene = mainMenu;
			}
		}
	}
}


bool Pause::GetGamePaused()
{
	return gamePaused;
}

void Pause::PauseGame()
{
	gamePaused = true;
}

void Pause::UnpauseGame()
{
	gamePaused = false;
}
