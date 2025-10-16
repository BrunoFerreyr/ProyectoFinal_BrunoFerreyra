#include "Map.h"

class LevelCave : public Map
{
public:
	LevelCave(const std::string& filePath, ManagersData& managersData);
	~LevelCave() override;

	void Initialize() override;
	void PlayBackgroundMusic() override;
	void LoadCamp();
	Asset* goToCamp;
};