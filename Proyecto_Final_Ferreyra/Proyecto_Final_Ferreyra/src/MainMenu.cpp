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
	sf::Font& font = resources.GetFont("../fonts/dogicapixel.ttf");

	sf::Texture& creditsBackgroundTexture = resources.GetTexture("../textures/menu/creditsBackground.png", false,sf::IntRect({ 0, 0 }, { 600, 600 }));
	creditsBackground = new sf::Sprite(creditsBackgroundTexture);
	creditsBackground->setPosition({ 640.0f, 60.0f });

	creditsText = new sf::Text(font);
	creditsText->setString("Game developed by:\n\n- John Doe\n- Jane Smith\n- Alice Johnson\n- Bob Brown\n\nThank you for playing!");
	creditsText->setCharacterSize(24);
	creditsText->setPosition({ creditsBackground->getPosition().x + 20.0f, creditsBackground->getPosition().y + 20.0f });
	startButton = new ButtonAsset({ &resources.GetTexture("../textures/StartButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 300.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr },font,"START",nullptr);
	creditsButton = new ButtonAsset({ &resources.GetTexture("../textures/StartButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 400.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr }, font, "CREDITS", nullptr);
	exitButton = new ButtonAsset({ &resources.GetTexture("../textures/StartButton.png", false, sf::IntRect()), sf::Vector2f{460.0f, 500.0f}, sf::IntRect({ 0, 0 }, { 361, 88 }), true , true, nullptr }, font, "EXIT", nullptr);
	musicVolumeSlider = new Slider(resources, "../textures/menu/musicSliderBackground.png", {150,350}, [this](float value) { this->audioManager.SetMusicVolume(value); });
	sfxVolumeSlider = new Slider(resources, "../textures/menu/sfxSliderBackground.png", { 190,350 }, [this](float value) { this->audioManager.SetSFXVolume(value); });

	Initialize();
}
MainMenu::~MainMenu()
{
	delete background;
	delete creditsBackground;
	delete creditsText;
	delete startButton;
	delete creditsButton;
	delete exitButton;
	delete musicVolumeSlider;
	delete sfxVolumeSlider;
}
void MainMenu::Initialize()
{
	std::string musicPath = "../audios/mainmenuMusic.ogg";
	audioManager.PlayMusic(musicPath);
}
void MainMenu::Input()
{
}
void MainMenu::Update(float deltaTime)
{
	if(musicVolumeSlider->GetIsDragging()){
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		musicVolumeSlider->Drag(pixelPos);
	}
	if(sfxVolumeSlider->GetIsDragging()) {
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sfxVolumeSlider->Drag(pixelPos);
	}
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

	window.draw(*musicVolumeSlider->GetSliderBackground());
	window.draw(*musicVolumeSlider->GetSliderBar());
	window.draw(*musicVolumeSlider->GetCircleShape());

	window.draw(*sfxVolumeSlider->GetSliderBackground());
	window.draw(*sfxVolumeSlider->GetSliderBar());
	window.draw(*sfxVolumeSlider->GetCircleShape());

	if (showCredits)
	{
		window.draw(*creditsBackground);
		window.draw(*creditsText);
	}
}
void MainMenu::HandleEvents(const sf::Event& event)
{
	if (const auto* mouse = event.getIf<sf::Event::KeyReleased>()) {
		if (mouse->code == sf::Keyboard::Key::R) 
		{
			if (testBuffer.loadFromFile("../audios/battleMusic.ogg")) {
				audioManager.PlaySFX(testBuffer);
			}
		}
		if (mouse->code == sf::Keyboard::Key::F)
		{
			if (testBuffer2.loadFromFile("../audios/caveMusic.ogg")) {
				audioManager.PlaySFX(testBuffer2);
			}
		}
	}

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
				ToggleCredits();
			}
			if (exitButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				ExitGame();
			}
			if (musicVolumeSlider->GetCircleShape()->getGlobalBounds().contains(worldPos)) 
			{
				musicVolumeSlider->SetIsDragging(true);
			}
			if (sfxVolumeSlider->GetCircleShape()->getGlobalBounds().contains(worldPos))
			{
				sfxVolumeSlider->SetIsDragging(true);
			}
		}
	}
	if (const auto* mouse = event.getIf<sf::Event::MouseButtonReleased>()) 
	{
		if (mouse->button == sf::Mouse::Button::Left) 
		{
			musicVolumeSlider->SetIsDragging(false);
			sfxVolumeSlider->SetIsDragging(false);
		}
	}
}
void MainMenu::LoadGame() 
{
	wantsChange = true;
	nextSceneID = SceneID::Gameplay;
	audioManager.PlaySFX(startButton->GetBuffer());
}
void MainMenu::ToggleCredits()
{
	showCredits = !showCredits;
	audioManager.PlaySFX(startButton->GetBuffer());
}
void MainMenu::ExitGame()
{
	SetWantsExit(true);
}