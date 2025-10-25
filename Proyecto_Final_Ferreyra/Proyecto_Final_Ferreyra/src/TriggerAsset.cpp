#include "TriggerAsset.h"
TriggerAsset::TriggerAsset(AssetData assetData, std::function<void()> func)
	: Asset(assetData)
{
	SetOnTriggerEnter(std::move(func));
	this->data.assetType = AssetType::Trigger;
}
TriggerAsset::~TriggerAsset()
{
}
bool TriggerAsset::SetCollision(bool collision)
{
	data.haveCollision = collision;
	return data.haveCollision;
}
bool TriggerAsset::GetCollision() const
{
	return data.haveCollision;
}
void TriggerAsset::SetOnTriggerEnter(std::function<void()> func)
{
	onTriggerEnterFunc = std::move(func);
}
void TriggerAsset::OnTriggerEnter()
{
	if (onTriggerEnterFunc && data.haveCollision) 
	{
		onTriggerEnterFunc();
	}
}
