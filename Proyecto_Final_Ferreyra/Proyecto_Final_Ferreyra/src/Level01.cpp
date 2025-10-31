#include "Level01.h"

Level01::Level01(const std::string& filePath, ManagersData& managersData, std::function<void()> resetPositions) : Map(filePath,managersData,resetPositions)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	firstTimePosition = { 600.0f, 570.0f };
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{0.0f ,720.0f - 67.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true , false, nullptr}));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 578.0f ,720.0f - 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true, false, nullptr}));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/wallup.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(1280, 68)), true, false, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/wallleft.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true, false, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/wallright.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 68.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true, false, nullptr }));

	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/bed.png", false, sf::IntRect()), sf::Vector2f{ 100.0f, 100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100, 180)), true, true, nullptr }));
	goToWoods = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 720.0f, 720.0f - 20.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true , false, nullptr}, [this]() { this->LoadLevel(MapID::Camp, firstTimePosition); });
	assetsObjects.push_back(goToWoods);

	assetsObjects.push_back(new InteractableAsset({ &resourceManager.GetTexture("../textures/oldWoman.png", false, sf::IntRect()), sf::Vector2f{ 910.0f, 170.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(57, 90)), true, true, nullptr}, [this]() {this->StartDialog(); }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/collisionCube.png", false, sf::IntRect()), sf::Vector2f{ 920.0f, 180.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(30, 60)), true, false ,nullptr ,AssetType::Static }));

	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/house/table.png", false, sf::IntRect()), sf::Vector2f{ 80.0f, 512.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(216, 120)), true, true, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/house/plant.png", false, sf::IntRect()), sf::Vector2f{ 1150.0f, 425.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(69, 77)), true, true, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/house/rug.png", false, sf::IntRect()), sf::Vector2f{ 500.0f, 360.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(194, 123)), false, true, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/house/miniTable.png", false, sf::IntRect()), sf::Vector2f{ 213.0f, 109.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(64, 75)), true, true, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/house/wardrobe.png", false, sf::IntRect()), sf::Vector2f{ 500.0f, 30.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(110, 181)), true, true, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/house/bed.png", false, sf::IntRect()), sf::Vector2f{ 50.0f, 80.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(159, 234)), true, true, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/house/library.png", false, sf::IntRect()), sf::Vector2f{ 737.0f, 582.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(174, 93)), true, true, nullptr }));

	playerInitPosition = firstTimePosition;

	nextMapsIDs.push_back(MapID::Camp);

	enterStepsBuffer.loadFromFile("../../res/audios/sfx/sfx_enterHardSteps.ogg");
	earnKeyBuffer.loadFromFile("../../res/audios/sfx/sfx_earnKey.ogg");
	this->CreateAssets();
}
Level01::~Level01()
{
	goToWoods = nullptr;
}

void Level01::Initialize()
{
	PlayBackgroundMusic();

	Map::Initialize();
}

void Level01::StartDialog()
{
	if (!missionsManager.HasWoodsKey()) 
	{
		dialog->Start(0, 5, [this]() 
			{ 
				missionsManager.SetWoodsKey(true); 
				audioManager.PlaySFX(earnKeyBuffer);
			});
		return;
	}
	if (!missionsManager.GetMetalsMissionStatus())
	{
		dialog->Start(6, 6, nullptr);
		return;
	}
	
	if (!missionsManager.HasCastleEntranceKey())
	{
		dialog->Start(7, 15, [this]() 
			{ 
				missionsManager.SetCastleEntranceKey(true); 
				audioManager.PlaySFX(earnKeyBuffer);
			});
		return;
	}
	dialog->Start(16, 16, nullptr);	
}
void Level01::PlayBackgroundMusic()
{
	std::string musicPath = "../../res/audios/houseMusic.ogg";
	audioManager.PlayMusic(musicPath);
}



