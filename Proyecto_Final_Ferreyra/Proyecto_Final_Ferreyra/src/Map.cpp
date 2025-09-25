#include "Map.h"

Map::Map(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog)
{
	//floor = nullptr;
	npc = new NPC("../textures/oldWoman.png", sf::Vector2i(69, 112), resourceManager, dialog);
	interactables.push_back(npc);

	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	assetsWall.push_back(new Asset(&resourceManager.GetTexture("../textures/walldownLeft.png",false,sf::IntRect()), sf::Vector2f{ 0.0f ,720.0f - 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true));
	assetsWall.push_back(new Asset(&resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{1280.0f - 578.0f ,720.0f - 67.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true));
	assetsWall.push_back(new Asset(&resourceManager.GetTexture("../textures/wallup.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(1280, 68)), true));
	assetsWall.push_back(new Asset(&resourceManager.GetTexture("../textures/wallleft.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true));
	assetsWall.push_back(new Asset(&resourceManager.GetTexture("../textures/wallright.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 68.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true));

	assetsObjects.push_back(new Asset(&resourceManager.GetTexture("../textures/bed.png", false, sf::IntRect()), sf::Vector2f{ 100.0f, 100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100, 180)), true));

	for (auto wall : assetsWall)
	{
		walls.push_back(wall->sprite);
	}
	for (auto asset : assetsObjects)
	{
		assets.push_back(asset->sprite);
	}
	/*textureWalls.loadFromFile("../textures/wall.png");
		

	//floor->setScale({ 1.0f, 1.0f });

	const int wallWidth = textureWalls.getSize().x;
	const int wallHeight = textureWalls.getSize().y;
	const int windowWidth = 1280;
	const int windowHeight = 720;

	// Superior e inferior
	/*for (int x = 0; x < windowWidth; x += wallWidth) {
		sf::Sprite* top = new sf::Sprite (textureWalls);
		top->setPosition({ (float)x, 0});
		walls.push_back(top);

		sf::Sprite* bottom = new sf::Sprite(textureWalls);
		bottom->setPosition({(float)x, (float)windowHeight - wallHeight });
		walls.push_back(bottom);
	}

	// Izquierda y derecha
	for (int y = wallHeight; y < windowHeight - wallHeight; y += wallHeight) {
		sf::Sprite* left = new sf::Sprite(textureWalls);
		left->setPosition({0, (float)y});
		walls.push_back(left);

		sf::Sprite* right = new sf::Sprite(textureWalls);
		right->setPosition({ (float)windowWidth - wallWidth, (float)y });
		walls.push_back(right);
	}
	*/
}
Map::~Map()
{
	for (auto wall : assetsWall)
	{
		delete wall;
	}
	walls.clear();
	for (auto asset : assetsObjects)
	{
		delete asset;
	}
	assets.clear();
	//delete floor;
}

void Map::Draw(sf::RenderWindow& window)
{
	if (floor)
	{
		window.draw(*floor);
	}
	for (auto wall : walls)
	{
		window.draw(*wall);
	}
	for (auto asset : assets)
	{
		window.draw(*asset);
	}
	window.draw(*npc->sprite);
}
bool Map::CheckCollision(const sf::FloatRect& playerBounds, bool isInteractable)
{
	if (!isInteractable) 
	{
		for (auto wall : walls)
		{
			if (wall->getGlobalBounds().findIntersection(playerBounds))
			{
				return true;
			}
		}
		for (auto asset : assets)
		{
			if (asset->getGlobalBounds().findIntersection(playerBounds))
			{
				return true;
			}
		}
	}
	else 
	{
		std::cout << "Checking interaction..." << std::endl;
		for (auto interactable : interactables)
		{
			if (interactable->sprite->getGlobalBounds().findIntersection(playerBounds))
			{
				interactable->Interact();
				return true;
			}
		}
	}
	
	return false;
}
