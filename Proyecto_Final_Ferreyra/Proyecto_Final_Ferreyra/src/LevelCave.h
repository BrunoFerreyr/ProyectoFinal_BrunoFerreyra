#include "Map.h"

class LevelCave : public Map
{
public:
	LevelCave(const std::string& filePath, ResourceManager& resourceManager, Dialog& dialog, AudioManager& audioManager);
	~LevelCave() override;

	Asset* goToCamp;
	void LoadCamp();
};