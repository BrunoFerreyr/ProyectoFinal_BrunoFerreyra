#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window, ResourceManager& resources, AudioManager& audioManager) 
	: Scene(window),  
	audioManager(audioManager),
	text(resources.GetFont("../../res/fonts/dogicapixel.ttf"),"COMENZAR", 48)
{
	std::string backgroundPath = "../../res/textures/MainMenuBackground.png";
	sf::IntRect backgroundArea({ 0, 0 }, { 1280, 720 });

	sf::Texture& backgroundTexture = resources.GetTexture(backgroundPath,false, backgroundArea);
	background = new sf::Sprite(backgroundTexture);
	sf::Font& font = resources.GetFont("../../res/fonts/dogicapixel.ttf");

	sf::Texture& creditsBackgroundTexture = resources.GetTexture("../textures/menu/creditsBackground.png", false,sf::IntRect({ 0, 0 }, { 518, 336 }));
	creditsBackground = new sf::Sprite(creditsBackgroundTexture);
	creditsBackground->setPosition({ 640.0f, 240.0f });

	sf::Texture& controlsBackgroundTexture = resources.GetTexture("../textures/menu/controlsBackground.png", false, sf::IntRect({ 0, 0 }, { 518, 336 }));
	controlsBackground = new sf::Sprite(controlsBackgroundTexture);
	controlsBackground->setPosition({ 640.0f, 240.0f });

	creditsText = new sf::Text(font);
	creditsText->setString(
	"Game developed during a course in\n"
	"\n"
	"ImageCampus by : Bruno Ferreyra\n"  
	"\n"
    "Sprites Characters :\n"
	"\n"
	"Digimon World 3 Bandai Namco Entertainment\n"
    "\n"
    "SFX : Itch.io\n"
    "Helton Yan\n"
    "Beto Bezerra\n"
    "\n"
    "OST : Itch.io\n"
    "alkakrab04@gmail.com\n"
    "\n"
    "UI: Itch.io, Craftpix.net\n"
    "Free Mining Pixel 32×32 Icons\n"
	"karsiori\n"
	"\n"
	"Thank you for playing!");
	creditsText->setCharacterSize(12);
	creditsText->setLineSpacing(1.5f);
	creditsText->setPosition({ creditsBackground->getPosition().x + 20.0f, creditsBackground->getPosition().y + 20.0f });
	startButton = new ButtonAsset({ &resources.GetTexture("../textures/menu/startButton.png", false, sf::IntRect()), sf::Vector2f{532.0f, 300.0f}, sf::IntRect({ 0, 0 }, { 216, 52 }), true , true, nullptr },font,"START");
	controlsButton = new ButtonAsset({ &resources.GetTexture("../textures/menu/startButton.png", false, sf::IntRect()), sf::Vector2f{532.0f, 360.0f}, sf::IntRect({ 0, 0 }, { 216, 52 }), true , true, nullptr }, font, "CONTROLS");
	creditsButton = new ButtonAsset({ &resources.GetTexture("../textures/menu/startButton.png", false, sf::IntRect()), sf::Vector2f{532.0f, 420.0f}, sf::IntRect({ 0, 0 }, { 216, 52 }), true , true, nullptr }, font, "CREDITS");
	exitButton = new ButtonAsset({ &resources.GetTexture("../textures/menu/startButton.png", false, sf::IntRect()), sf::Vector2f{532.0f, 480.0f}, sf::IntRect({ 0, 0 }, { 216, 52 }), true , true, nullptr }, font, "EXIT");
	musicVolumeSlider = new Slider(resources, "../textures/menu/musicSliderBackground.png", {360,330}, [this](float value) { this->audioManager.SetMusicVolume(value); });
	sfxVolumeSlider = new Slider(resources, "../textures/menu/sfxSliderBackground.png", { 400,330 }, [this](float value) { this->audioManager.SetSFXVolume(value); });

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
	delete controlsButton;
	delete controlsBackground;
}
void MainMenu::Initialize()
{
	std::string musicPath = "../../res/audios/mainmenuMusic.ogg";
	audioManager.PlayMusic(musicPath);
	sceneID = SceneID::MainMenu;
}
void MainMenu::Input()
{
}
void MainMenu::Update(float deltaTime)
{
	if(musicVolumeSlider->GetIsDragging())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		musicVolumeSlider->Drag(pixelPos);
	}
	if(sfxVolumeSlider->GetIsDragging()) 
	{
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
	window.draw(*controlsButton->GetSprite());
	window.draw(*controlsButton->GetText());
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
	if (showControls)
	{
		window.draw(*controlsBackground);
	}
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
			if (controlsButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				ToggleControls();
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
	if (showControls) 
	{
		return;
	}
	showCredits = !showCredits;
	audioManager.PlaySFX(startButton->GetBuffer());
}
void MainMenu::ToggleControls()
{
	if (showCredits)
	{
		return;
	}
	showControls = !showControls;
	audioManager.PlaySFX(startButton->GetBuffer());
}
void MainMenu::ExitGame()
{
	SetWantsExit(true);
}