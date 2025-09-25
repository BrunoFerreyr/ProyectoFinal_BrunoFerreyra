#include "Game.h"
//IF NOT EXIST "$(TargetDir)res\" MKDIR "$(TargetDir)res\"
//XCOPY "$(ProjectDir)res\" "$(TargetDir)res\" /e /h /y /s
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
	CreateWindow();
	GetFont();
	CreateMap();
	CreatePlayer();
}
void Game::GameLoop()
{
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
	//window.create(sf::VideoMode({ 800, 600 }), "Mi primer juego");
	window = new sf::RenderWindow(sf::VideoMode({ windowsWidth, windowsHeight }), "Mi primer juego");
	window->setFramerateLimit(60);
	/*sf::View view;
	view.move({ -200,-200});*/
}
void Game::GetFont()
{
	dialog = new Dialog(resourceManager);	
}
void Game::CreatePlayer()
{
	std::string path = "../textures/PlayerIdle.png";
	sf::Vector2i spriteSheetSize = { 47, 60 };
	player = new Player(path, spriteSheetSize, resourceManager,maps[0], dialog);
}
void Game::CreateMap() 
{
	Map* map = new Map("../textures/floor.png", resourceManager, *dialog);
	maps.push_back(map);	
}
void Game::Input()
{
	HandleEvents();
	player->Input();
	//currentScene->Input();
}
void Game::HandleEvents() 
{
	while (const auto event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window->close();

		player->HandleEvents(*event);
		//currentScene->HandleEvents(*event);
	}
}
void Game::Update()
{
	float deltaTime = clockk.restart().asSeconds();
	player->Update(deltaTime);
	//currentScene->Update(deltaTime);
}
void Game::Draw() 
{
	window->clear();
	maps[0]->Draw(*window);
	//currentScene->Draw();
	player->Draw(*window);
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
}
void Game::DestroyMaps()
{
	for (size_t i = 0; i < maps.size(); i++)
	{
		delete maps[i];
	}
}