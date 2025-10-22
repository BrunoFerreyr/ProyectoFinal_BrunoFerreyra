#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window, ResourceManager& resources, AudioManager& audioManager) 
	: Scene(window),  
	audioManager(audioManager),
	text(resources.GetFont("../fonts/dogicapixel.ttf"),"COMENZAR", 48)
{
	std::string backgroundPath = "../textures/MainMenuBackground.png";
	sf::IntRect backgroundArea({ 0, 0 }, { 1280, 720 });

	sf::Texture& backgroundTexture = resources.GetTexture(backgroundPath,false, backgroundArea);
	background = new sf::Sprite(backgroundTexture);
	std::string fontPath = "../fonts/dogicapixel.ttf";
	sf::Font& font = resources.GetFont(fontPath);

	startButton = new ButtonAsset({ &resources.GetTexture("../textures/StartButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 300.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr },font,"START",nullptr);
	creditsButton = new ButtonAsset({ &resources.GetTexture("../textures/StartButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 400.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr }, font, "CREDITS", nullptr);
	exitButton = new ButtonAsset({ &resources.GetTexture("../textures/StartButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 500.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr }, font, "EXIT", nullptr);
	
	std::string musicPath = "../audios/mainmenuMusic.ogg";
	audioManager.PlayMusic(musicPath);
}
MainMenu::~MainMenu()
{
	delete background;
	delete startButton;
}
void MainMenu::Input()
{
}
void MainMenu::Update(float deltaTime)
{
	if (wantsChange)
	{
		return;
	}
}
void MainMenu::Draw()
{
	window.draw(*background);
	window.draw(*startButton->GetSprite());
	window.draw(*startButton->GetText());
	window.draw(*creditsButton->GetSprite());
	window.draw(*creditsButton->GetText());
	window.draw(*exitButton->GetSprite());
	window.draw(*exitButton->GetText());
}
void MainMenu::HandleEvents(const sf::Event& event)
{
	if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) 
	{
		if (mouse->button == sf::Mouse::Button::Left) 
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			if (startButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				LoadGame();
			}
			if (creditsButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				ShowCredits();
			}
			if (exitButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				ExitGame();
			}
		}
	}
}
void MainMenu::LoadGame() 
{
	wantsChange = true;
	nextSceneID = SceneID::Gameplay;
}
void MainMenu::ShowCredits()
{
	std::cout << "Showing credits..." << std::endl;
	//wantsChange = true;
	//nextSceneID = SceneID::Credits;
}
void MainMenu::ExitGame()
{
	std::cout << "Exiting game..." << std::endl;
	//window.close();
}