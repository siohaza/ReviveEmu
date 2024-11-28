#pragma once

class CSteamUserStats
{
public:
	CSteamUserStats();
	~CSteamUserStats();

	virtual int GetNumStats(CGameID a1);
	virtual int GetNumStats();
	virtual void GetStatName(CGameID a1, unsigned int a2);
	virtual void GetStatType(CGameID a1, char  const* a2);
	virtual int GetNumAchievements(CGameID a1);
	virtual const char* GetAchievementName(CGameID a1, unsigned int a2);
	virtual int GetNumGroupAchievements(CGameID a1);
	virtual void GetGroupAchievementName(CGameID a1, unsigned int a2);
	virtual int RequestCurrentStats(CGameID a1);
	virtual int GetStat(CGameID a1, char  const* a2, int * a3);
	virtual int GetStat(CGameID a1, char  const* a2, float * a3);
	virtual void SetStat(CGameID a1, char  const* a2, int a3);
	virtual void SetStat(CGameID a1, char  const* a2, float a3);
	virtual void UpdateAvgRateStat(CGameID a1, char  const* a2, float a3, double a4);
	virtual bool GetAchievement(CGameID a1, char  const* a2, bool * a3);
	virtual bool GetGroupAchievement(CGameID a1, char  const* a2, bool * a3);
	virtual void SetAchievement(CGameID a1, char  const* a2);
	virtual void SetGroupAchievement(CGameID a1, char  const* a2);
	virtual void StoreStats(CGameID a1);
	virtual void ClearAchievement(CGameID a1, char  const* a2);
	virtual void ClearGroupAchievement(CGameID a1, char  const* a2);
	virtual void GetAchievementIcon(CGameID a1, char  const* a2);
	virtual void GetAchievementDisplayAttribute(CGameID a1, char  const* a2, char  const* a3);
	virtual void IndicateAchievementProgress(CGameID a1, char  const* a2, unsigned int a3, unsigned int a4);
};

CSteamUserStats* GSteamUserStats(void);