#include "Level01.h"

Level01::Level01(const std::string& filePath, ManagersData& managersData) : Map(filePath,managersData)
{
	//floor = nullptr;

	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{0.0f ,720.0f - 67.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true , true, nullptr}));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/walldownLeft.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 578.0f ,720.0f - 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(578, 67)), true, true, nullptr}));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/wallup.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 0.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(1280, 68)), true, true, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/wallleft.png", false, sf::IntRect()), sf::Vector2f{ 0.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true, true, nullptr }));
	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/wallright.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 68.0f, 67.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(68, 585)), true, true, nullptr }));

	assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/bed.png", false, sf::IntRect()), sf::Vector2f{ 100.0f, 100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(100, 180)), true, true, nullptr }));
	goToWoods = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 1280.0f - 720.0f, 720.0f - 20.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true , true, nullptr}, [this]() { this->LoadLevel(MapID::Camp, { 1280.0f - 680.0f, 720.0f - 150.0f }); });
	assetsObjects.push_back(goToWoods);

	assetsObjects.push_back(new InteractableAsset({ &resourceManager.GetTexture("../textures/oldWoman.png", false, sf::IntRect()), sf::Vector2f{ 600.0f, 600.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(57, 90)), true, true, nullptr}, [this]() {this->StartDialog(); }));
	
	playerInitPosition = {1280.0f - 680.0f, 720.0f - 150.0f };

	nextMapsIDs.push_back(MapID::Camp);
	SetNextMap(nextMapsIDs[0]);

	enterStepsBuffer.loadFromFile("../audios/sfx/sfx_enterHardSteps.ogg");
	earnKeyBuffer.loadFromFile("../audios/sfx/sfx_earnKey.ogg");
	//audioManager.PlayMusic(musicPath);
	this->CreateAssets();
}
Level01::~Level01()
{
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
	std::string musicPath = "../audios/houseMusic.ogg";
	audioManager.PlayMusic(musicPath);
}



