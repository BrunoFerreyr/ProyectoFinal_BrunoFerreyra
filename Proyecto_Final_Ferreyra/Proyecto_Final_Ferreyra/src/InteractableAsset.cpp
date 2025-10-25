#include "InteractableAsset.h"
InteractableAsset::InteractableAsset(AssetData assetData, std::function<void()> function)
	: Asset(assetData)
{
	SetOnTriggerInteract(std::move(function));
	this->data.assetType = AssetType::Interactable;
}
InteractableAsset::~InteractableAsset()
{
}

void InteractableAsset::SetOnTriggerInteract(std::function<void()> function)
{
	onInteractFunction = std::move(function);
}

void InteractableAsset::IdleAnimation(float deltaTime)
{
	if (haveIdleAnimation) 
	{
		
	}
}

void InteractableAsset::Interact()
{
	if (onInteractFunction) 
	{
		onInteractFunction();
	}
}


