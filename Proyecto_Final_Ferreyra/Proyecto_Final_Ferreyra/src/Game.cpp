#include "Game.h"
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
	DestroyScenes();
	DestroyPlayer();
}
void Game::CreateWindow()
{
	unsigned int windowsWidth = 1280;
	unsigned int windowsHeight = 720;
	window = new sf::RenderWindow(sf::VideoMode({ windowsWidth, windowsHeight }), "Mi primer juego");

	window->setFramerateLimit(60);	
}
void Game::CreateManagers()
{
	dialog = new Dialog(resourceManager);
	collectablesUI = new CollectablesUI(resourceManager, missionsManager);
	managersData = new ManagersData{ resourceManager, audioManager, missionsManager, dialog, collectablesUI };
}
void Game::CreatePlayer()
{
	std::string path = "../../res/textures/PlayerIdle.png";
	sf::Vector2i spriteSheetSize = { 378, 768 };
	player = new Player(path, spriteSheetSize, resourceManager, dialog, audioManager);
}
void Game::CreateScenes()
{
	mainMenu = new MainMenu(*window, resourceManager, audioManager);
	pauseManager = new Pause(resourceManager,audioManager, *window, *&currentScene, *&mainMenu);

	scenes.emplace(SceneID::MainMenu, mainMenu);
}

void Game::Input()
{
	HandleEvents();

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
	float deltaTime = clock.restart().asSeconds();
	currentScene->Update(deltaTime);


	if (currentScene->GetWantsChange())
	{
		currentScene->SetWantsChange(false);
		if (currentScene->GetSceneID() == SceneID::MainMenu) {			
			gameplay = new Gameplay(*window, player, *pauseManager, *managersData);
			scenes.emplace(SceneID::Gameplay, gameplay);
		}

		if (currentScene->GetSceneID() == SceneID::Gameplay)
		{
			currentScene = scenes.find(currentScene->GetNextSceneID())->second;
			delete gameplay;
			gameplay = nullptr;
			DestroyPlayer();
			CreateManagers();
			CreatePlayer();
			scenes.erase(SceneID::Gameplay);
		}
		else
		{
			currentScene = scenes.find(currentScene->GetNextSceneID())->second;
		}

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
	delete collectablesUI;
}
void Game::DestroyScenes()
{
	currentScene = nullptr;
	for (auto scene : scenes)
	{
		delete scene.second;
	}
	scenes.clear();
	gameplay = nullptr;
	mainMenu = nullptr;

	delete pauseManager;
}