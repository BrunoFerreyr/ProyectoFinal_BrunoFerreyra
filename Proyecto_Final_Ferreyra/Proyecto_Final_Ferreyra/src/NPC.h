#pragma once
#include <iostream>
#include "ResourceManager.h"
#include "Interactable.h"
#include "Dialog.h"
class NPC : public Interactable
{
public:
	NPC(const std::string& path, const sf::Vector2i& spriteSheetSize, ResourceManager& resourceManager, Dialog& dialog);
	~NPC();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Interact() override;

private:
	ResourceManager& resourceManager;
	float speed;
	sf::Vector2f direction;
	Dialog* dialog;
};