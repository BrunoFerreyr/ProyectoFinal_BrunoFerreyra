#include "NPC.h"
NPC::NPC(const std::string& path, const sf::Vector2i& spriteSheetSize, ResourceManager& resourceManager, Dialog& dialog)
	:resourceManager(resourceManager)
{
	sf::IntRect area({ 0,0 }, spriteSheetSize);
	sf::Texture& texture = resourceManager.GetTexture(path, false, area);
	sprite = new sf::Sprite(texture);
	//sprite->setTextureRect(currentValue); ver para animacion
	sprite->setPosition({ 1000.0f, 400.0f });
	sprite->setScale({ 2.0f, 2.0f });
	speed = 200.0f;

	this->dialog = &dialog;
}
NPC::~NPC()
{
	delete sprite;
}
void NPC::Interact()
{
	//AGREGAR DELEGATE ACA PARA QUE SEA REUTILIZABLE
	if (!dialog->IsActive()) 
	{
		dialog->Start(0, 3);
	}	
	//std::cout << "Interacting with NPC" << std::endl;
	//Interactable::Interact();, puedo llamar al padre si no la hago abstacta. a FUTURO
}
void NPC::Update(float deltaTime)
{
	//Movement(deltaTime);
}
void NPC::Draw(sf::RenderWindow& window)
{
	//window.draw(*sprite);
}