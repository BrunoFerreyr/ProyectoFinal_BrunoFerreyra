#pragma once
#include "Map.h"
class Level02 : public Map
{
public:
	Level02(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog);
	~Level02() override;
};

