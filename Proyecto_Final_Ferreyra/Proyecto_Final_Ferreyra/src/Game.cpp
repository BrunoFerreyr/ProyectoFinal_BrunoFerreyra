#include "Game.h"
//IF NOT EXIST "$(TargetDir)res\" MKDIR "$(TargetDir)res\"
//XCOPY "$(ProjectDir)res\" "$(TargetDir)res\" /e /h /y /s
//https://alkakrab.itch.io/free-12-tracks-pixel-rpg-game-music-pack
//https://karsiori.itch.io/pixel-art-key-pack-animated
//https://craftpix.net/freebies/free-mining-pixel-32x32-icons/?srsltid=AfmBOooNsua5TJ0V6sMYV_OfdhMAg0-ecYfJi1iaSNOii4fPzB8LuLWm
Game::Game()
{

}
Game::~Game()
{
}
void Game::Play()
{
	Initialize();
	GameLoop();
	DeInitialize();
}
void Game::Initialize()
{
	srand(time(nullptr));

	CreateWindow();
	CreateManagers();
	CreatePlayer();
	CreateScenes();
}
void Game::GameLoop()
{
	currentScene = scenes.find(SceneID::MainMenu)->second;
	while (window->isOpen())
	{
		Input();
		Update();
		Draw();
	}
}
void Game::DeInitialize()
{
	DestroyWindow();
	DestroyPlayer();
}
void Game::CreateWindow()
{
	unsigned int windowsWidth = 1280;
	unsigned int windowsHeight = 720;
	window = new sf::RenderWindow(sf::VideoMode({ windowsWidth, windowsHeight }), "Mi primer juego");
	window->setFramerateLimit(60);
	/*sf::View view;
	view.move({ -200,-200});*/
}
void Game::CreateManagers()
{
	dialog = new Dialog(resourceManager);
	collectablesUI = new CollectablesUI(resourceManager, missionsManager);
	managersData = new ManagersData{ resourceManager, audioManager, missionsManager, dialog, collectablesUI };
}
void Game::CreatePlayer()
{
	std::string path = "../textures/PlayerIdle.png";
	sf::Vector2i spriteSheetSize = { 378, 768 };
	player = new Player(path, spriteSheetSize, resourceManager, dialog);
}
void Game::CreateScenes()
{
	mainMenu = new MainMenu(*window, resourceManager, audioManager);
	pauseManager = new Pause(resourceManager, *window, *&currentScene, *&mainMenu);//DO  ver signos

	gameplay = new Gameplay(*window, player, *pauseManager, *managersData);

	scenes.emplace(SceneID::MainMenu, mainMenu);
	scenes.emplace(SceneID::Gameplay, gameplay);
}

void Game::Input()
{
	HandleEvents();
	//player->Input();
	currentScene->Input();
}
void Game::HandleEvents() 
{
	while (const auto event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>()) 
		{
			window->close();
		}

		currentScene->HandleEvents(*event);
	}
}
void Game::Update()
{
	float deltaTime = clockk.restart().asSeconds();
	currentScene->Update(deltaTime);

	if (currentScene->GetWantsChange()) 
	{
		currentScene->SetWantsChange(false);
		
		currentScene = scenes.find(currentScene->GetNextSceneID())->second;
		currentScene->Initialize();
	}

	if (currentScene->GetWantsExit()) 
	{
		window->close();
	}
}
void Game::Draw() 
{
	window->clear();
	currentScene->Draw();
	dialog->Draw(*window);
	window->display();
}
void Game::DestroyWindow()
{
	delete window;
}
void Game::DestroyPlayer()
{
	delete player;
	delete dialog;
	delete managersData;
}