#include "MissionsManager.h"
MissionsManager::MissionsManager()
{
}
MissionsManager::~MissionsManager()
{
}

void MissionsManager::HaveTalkedWithOldLady()
{
	if (metalsMission)
	{
		hasCastleEntranceKey = true;
		return;
	}
		
	hasWoodsKey = true;
}
void MissionsManager::CheckGetMetalsMission(int metalCount)
{
	if (!metalsMission && metalCount >= 5)
	{
		metalsMission = true;
	}
}
void MissionsManager::HaveDefeatedKnight()
{
	defeatKnightMission = true;
	hasCastleKey = true;
}

bool MissionsManager::GetMetalsMissionStatus() const
{
	return metalsMission;
}
bool MissionsManager::GetDefeatKnightMissionStatus() const
{
	return defeatKnightMission;
}

bool MissionsManager::HasWoodsKey() const
{
	return hasWoodsKey;
}
bool MissionsManager::HasCastleEntranceKey() const
{
	return hasCastleEntranceKey;
}
bool MissionsManager::HasCastleKey() const
{
	return hasCastleKey;
}
void MissionsManager::SetWoodsKey(bool status)
{
	hasWoodsKey = status;
}
void MissionsManager::SetCastleEntranceKey(bool status)
{
	hasCastleEntranceKey = status;
}
void MissionsManager::SetCastleKey(bool status)
{
	hasCastleKey = status;
}
void MissionsManager::ResetAll() 
{
	metalsMission = false;
	defeatKnightMission = false;
	hasWoodsKey = false;
	hasCastleEntranceKey = false;
	hasCastleKey = false;
}

