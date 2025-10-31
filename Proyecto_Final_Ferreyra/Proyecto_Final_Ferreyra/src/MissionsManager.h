#pragma once
class MissionsManager
{
public:
	MissionsManager();
	~MissionsManager();
	
	void HaveTalkedWithOldLady();
	void CheckGetMetalsMission(int metalCount);
	void HaveDefeatedKnight();
	bool GetMetalsMissionStatus() const;
	bool GetDefeatKnightMissionStatus() const;
	bool HasWoodsKey() const;
	bool HasCastleEntranceKey() const;
	bool HasCastleKey() const;
	void SetWoodsKey(bool status);
	void SetCastleEntranceKey(bool status);
	void SetCastleKey(bool status);
	void ResetAll();

private:
	bool metalsMission = false;
	bool defeatKnightMission = false;
	bool hasWoodsKey = false;
	bool hasCastleEntranceKey = false;
	bool hasCastleKey = false;
};