#pragma once
#include "ResourceManager.h"
#include "AudioManager.h"
#include "MissionsManager.h"
#include "Dialog.h"
#include "CollectablesUI.h"

struct ManagersData
{
	ResourceManager& resourceManager;
	AudioManager& audioManager;
	MissionsManager& missionsManager;
	Dialog* dialog;
	CollectablesUI* collectablesUI;
};