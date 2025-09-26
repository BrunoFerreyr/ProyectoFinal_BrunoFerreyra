#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window, ResourceManager& resources)
	: Scene(window),
	text(resources.GetFont("../fonts/dogicapixel.ttf"),"COMENZAR", 48)
{
	std::string backgroundPath = "../textures/MainMenuBackground.png";
	sf::IntRect backgroundArea({ 0, 0 }, { 1280, 720 });

	sf::Texture& backgroundTexture = resources.GetTexture(backgroundPath,false, backgroundArea);
	background = new sf::Sprite(backgroundTexture);

	std::string buttonPath = "../textures/StartButton.png";
	sf::IntRect buttonArea({ 0, 0 }, { 361, 88 });

	sf::Texture& buttonTexture = resources.GetTexture(buttonPath, false, buttonArea);
	startButton = new sf::Sprite(buttonTexture);

	startButton->setOrigin({startButton->getTexture().getSize().x * 0.5f, 
		startButton->getTexture().getSize().y * 0.5f });

	startButton->setPosition({ window.getSize().x * 0.5f, window.getSize().y * 0.5f });

	std::string fontPath = "../fonts/dogicapixel.ttf";
	sf::Font& font = resources.GetFont(fontPath);
	buttonText = new sf::Text(font,"COMENZAR", 48);

	buttonText->setFillColor(sf::Color::Black);
	buttonText->setOrigin(buttonText->getLocalBounds().getCenter());
	buttonText->setPosition(startButton->getPosition());

	/*
	std::string musicPath = "../res/audio/MainMenuMusic.ogg";
	music.openFromFile(musicPath);
	music.setLooping(true);
	music.setVolume(50.f);
	music.play();*/
}
MainMenu::~MainMenu()
{
	delete buttonText;
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

	if (music.getStatus() != sf::SoundSource::Status::Stopped)
	{		
		music.play();
	}
}
void MainMenu::Draw()
{
	window.draw(*background);
	window.draw(*startButton);
	window.draw(*buttonText);
}
void MainMenu::HandleEvents(const sf::Event& event)
{
	if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) 
	{
		if (mouse->button == sf::Mouse::Button::Left) 
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			if (startButton->getGlobalBounds().contains(worldPos))
			{
				wantsChange = true;
				nextSceneID = SceneID::Gameplay;

				//music.stop();
			}
		}
	}
}