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
	sf::Font& font = resources.GetFont("../fonts/dogicapixel.ttf");
	continueButton = new ButtonAsset({ &resources.GetTexture("../textures/continueButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 300.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr }, font, "CONTINUE", nullptr);
	mainMenuButton = new ButtonAsset({ &resources.GetTexture("../textures/mainmenuButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 400.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr }, font, "MAIN MENU", nullptr);
	exitButton = new ButtonAsset({ &resources.GetTexture("../textures/StartButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 500.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr }, font, "EXIT", nullptr);

	gamePaused = false;
}

Pause::~Pause() 
{
	delete continueButton;
	delete mainMenuButton;
	delete exitButton;
}

void Pause::Input() {}

void Pause::Draw()
{
	if (!gamePaused) return;

	//window.draw(*pauseBackground);
	window.draw(*continueButton->GetSprite());
	window.draw(*continueButton->GetText());
	window.draw(*mainMenuButton->GetSprite());
	window.draw(*mainMenuButton->GetText());
	window.draw(*exitButton->GetSprite());
	window.draw(*exitButton->GetText());
}

void Pause::HandleEvents(const sf::Event& event)
{
	if (isOnBattle) 
	{
		return;
	}
	if (const auto* key = event.getIf<sf::Event::KeyPressed>()) 
	{
		if (key->scancode == sf::Keyboard::Scancode::Enter) 
		{

			if (gamePaused) 
			{
				TogglePause(false);
			}
			else 
			{
				TogglePause(true);
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

			if (continueButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				TogglePause(false);
			}

			if (mainMenuButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				ReturnToMainMenu();
			}
			if (exitButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				ExitGame();
			}
		}
	}
}


bool Pause::GetGamePaused()
{
	return gamePaused;
}

void Pause::TogglePause(bool value)
{
	gamePaused = value;
}
void Pause::ReturnToMainMenu()
{
	TogglePause(false);
	currentScene->SetWantsChange(true);
	//currentScene = mainMenu;
}
void Pause::ExitGame()
{
	currentScene->SetWantsExit(true);
}
void Pause::SetIsOnBattle(bool onBattle)
{
	isOnBattle = onBattle;
}
