#include "InteractableAsset.h"
InteractableAsset::InteractableAsset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision, std::function<void()> func)
	: Asset(texture, pos, size, collision)
{
	SetOnTriggerInteract(std::move(func));
	this->data.assetType = AssetType::Interactable;
}
InteractableAsset::~InteractableAsset()
{
}
void InteractableAsset::SetOnTriggerInteract(std::function<void()> func)
{
	onInteractFunc = std::move(func);
	//ver de asignar todo desde el level01
}
void InteractableAsset::IdleAnimation(float deltaTime)
{
	if (haveIdleAnimation) {
		//DO AGREGAR ANIMACION, gameplay y vandalos, otros mapas
	}
}
void InteractableAsset::Interact()
{
	if (onInteractFunc) 
	{
		onInteractFunc();
	}
}
