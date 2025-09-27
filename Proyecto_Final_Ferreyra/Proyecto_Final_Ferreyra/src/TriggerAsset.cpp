#include "TriggerAsset.h"
TriggerAsset::TriggerAsset(sf::Texture* texture, const sf::Vector2f pos, sf::IntRect size, bool collision)
	: Asset(texture, pos, size, collision)
{
}
TriggerAsset::~TriggerAsset()
{
}
bool TriggerAsset::SetCollision(bool collision)
{
	haveCollision = collision;
	return haveCollision;
}
bool TriggerAsset::GetCollision() const
{
	return haveCollision;
}
void TriggerAsset::SetOnTriggerEnter(std::function<void()> func)
{
	onTriggerEnterFunc = std::move(func);
	//ver de asignar todo desde el level01
}
void TriggerAsset::OnTriggerEnter()
{
	if (onTriggerEnterFunc) {
		onTriggerEnterFunc();
	}
}
