#include "Pause.h"
Pause::Pause(ResourceManager& resources, AudioManager& audioManager, sf::RenderWindow& window, Scene*& currentScene, MainMenu*& mainMenu) :
	currentScene(currentScene), mainMenu(mainMenu), window(window), audioManager(audioManager)
{
	this->currentScene = currentScene;
	this->mainMenu = mainMenu;

	sf::Font& font = resources.GetFont("../fonts/dogicapixel.ttf");
	continueButton = new ButtonAsset({ &resources.GetTexture("../textures/continueButton.png", false, sf::IntRect()), sf::Vector2f{490.0f, 250.0f}, sf::IntRect({ 0, 0 }, { 300, 100 }), true , true, nullptr }, font, "CONTINUE");
	mainMenuButton = new ButtonAsset({ &resources.GetTexture("../textures/mainmenuButton.png", false, sf::IntRect()), sf::Vector2f{490.0f, 380.0f}, sf::IntRect({ 0, 0 }, { 300, 100 }), true , true, nullptr }, font, "MAIN MENU");
	exitButton = new ButtonAsset({ &resources.GetTexture("../textures/menu/startButton.png", false, sf::IntRect()), sf::Vector2f{532.0f, 510.0f}, sf::IntRect({ 0, 0 }, { 216, 52 }), true , true, nullptr }, font, "EXIT");
	musicVolumeSlider = new Slider(resources, "../textures/menu/musicSliderBackground.png", { 360,330 }, [this](float value) { this->audioManager.SetMusicVolume(value); });
	sfxVolumeSlider = new Slider(resources, "../textures/menu/sfxSliderBackground.png", { 400,330 }, [this](float value) { this->audioManager.SetSFXVolume(value); });

	enterPauseBuffer.loadFromFile("../audios/sfx/sfx_enterPause.ogg");
	exitPauseBuffer.loadFromFile("../audios/sfx/sfx_exitPause.ogg");

	gamePaused = false;
}
Pause::~Pause() 
{
	delete continueButton;
	delete mainMenuButton;
	delete exitButton;
	delete musicVolumeSlider;
	delete sfxVolumeSlider;
	currentScene = nullptr;
}

void Pause::Update(float deltaTime)
{
	if (musicVolumeSlider->GetIsDragging())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		musicVolumeSlider->Drag(pixelPos);
	}
	if (sfxVolumeSlider->GetIsDragging())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sfxVolumeSlider->Drag(pixelPos);
	}
}
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

	window.draw(*musicVolumeSlider->GetSliderBackground());
	window.draw(*musicVolumeSlider->GetSliderBar());
	window.draw(*musicVolumeSlider->GetCircleShape());

	window.draw(*sfxVolumeSlider->GetSliderBackground());
	window.draw(*sfxVolumeSlider->GetSliderBar());
	window.draw(*sfxVolumeSlider->GetCircleShape());
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
				audioManager.PlaySFX(exitPauseBuffer);
			}
			else 
			{
				TogglePause(true);
				audioManager.PlaySFX(enterPauseBuffer); 
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
				audioManager.PlaySFX(exitPauseBuffer);
				audioManager.PlaySFX(exitButton->GetBuffer());
			}

			if (mainMenuButton->GetSprite()->getGlobalBounds().contains(worldPos))
			{
				ReturnToMainMenu();
				audioManager.PlaySFX(exitButton->GetBuffer());
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
}

void Pause::ExitGame()
{
	currentScene->SetWantsExit(true);
}

void Pause::SetIsOnBattle(bool onBattle)
{
	isOnBattle = onBattle;
}
void Pause::SetIsOnDialog(bool onDialog)
{
	isOnDialog = onDialog;
}
