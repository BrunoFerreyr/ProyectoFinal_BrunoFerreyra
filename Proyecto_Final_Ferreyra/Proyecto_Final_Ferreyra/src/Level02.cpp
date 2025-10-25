#include "Level02.h"

Level02::Level02(const std::string& filePath, ManagersData& managersData) : Map(filePath, managersData)
{
	textureFloor.loadFromFile(filePath);
	floor = new sf::Sprite(textureFloor);
	
	goToHouse = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{1280.0f - 380.0f, -100.0f}, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true , true, nullptr }, [this]() { this->LoadLevel(MapID::OldWomanHouse, {950.0f, 100.0f}); });
	goToCave = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ 400.0f, 700.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, false, nullptr }, [this]() { this->LoadLevel(MapID::Cave, { 400.0f, 600.0f }); });
	goToWoods01 = new TriggerAsset({ &resourceManager.GetTexture("../textures/changeMapCollision.png", false, sf::IntRect()), sf::Vector2f{ -100.0f, 720.0f - 600.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(126, 126)), true, true, nullptr }, [this]() { this->LoadLevel(MapID::Woods01, { 64.0f, 140.0f }); });
	woodsDoor = new InteractableAsset({ &resourceManager.GetTexture("../textures/woodsDoor.png", false, sf::IntRect()), sf::Vector2f{ 10.0f, 100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(59, 195)), true, true ,nullptr }, [this]() {this->WoodsDoorInteraction(); });
	woodsDoorCollision = new Asset({ &resourceManager.GetTexture("../textures/woodsDoor.png", false, sf::IntRect()), sf::Vector2f{ 10.0f, 100.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(40, 195)), true, false ,nullptr ,AssetType::Static });

	assetsObjects.push_back(goToHouse);
	assetsObjects.push_back(goToCave);
	assetsObjects.push_back(goToWoods01);
	assetsObjects.push_back(woodsDoor);
	assetsObjects.push_back(woodsDoorCollision);
	//assetsObjects.push_back(new Asset({ &resourceManager.GetTexture("../textures/house/table.png", false, sf::IntRect()), sf::Vector2f{ 500.0f, 500.0f }, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(40, 195)), true, false ,nullptr }));
	playerInitPosition = { 400.0f, 600.0f };
	nextMapsIDs.push_back(MapID::OldWomanHouse);
	nextMapsIDs.push_back(MapID::Cave);
	nextMapsIDs.push_back(MapID::Woods01);
	

	enterStepsBuffer.loadFromFile("../audios/sfx/sfx_enterGrassSteps.ogg");

	this->CreateAssets();
}
Level02::~Level02()
{
}
void Level02::Initialize()
{
	PlayBackgroundMusic();
	
	Map::Initialize();
}

void Level02::PlayBackgroundMusic()
{
	std::string musicPath = "../audios/caveMusic.ogg";
	audioManager.PlayMusic(musicPath);
}

void Level02::WoodsDoorInteraction()
{
	if (missionsManager.HasWoodsKey())
	{
		//DO agregar asset eraser function
		EraseAsset(woodsDoor);
		EraseAsset(woodsDoorCollision);
		audioManager.PlaySFX(openDoorBuffer);
		/*assetsObjects.erase(std::remove(assetsObjects.begin(), assetsObjects.end(), woodsDoor), assetsObjects.end());
		assets.erase(std::remove(assets.begin(), assets.end(), woodsDoor->GetSprite()), assets.end());
		delete woodsDoor;
		woodsDoor = nullptr;*/

		
		
	}
	else
	{
		dialog->Start(100, 100, nullptr);
	}
}
