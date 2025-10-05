#include "Map.h"

class LevelCave : public Map
{
public:
	LevelCave(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog);
	~LevelCave() override;

	Asset* goToCamp;
	void LoadCamp();
};