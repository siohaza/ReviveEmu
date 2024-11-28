#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUserStats002.h"
#include ".\SteamUserStats.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUserStats* g_pSteamUserStats;

CSteamUserStats002::CSteamUserStats002()
{
}

CSteamUserStats002::~CSteamUserStats002()
{
}

	int CSteamUserStats002::GetNumStats(CGameID a1)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetNumStats(a1); 
	}
	void CSteamUserStats002::GetStatName(CGameID a1, unsigned int a2)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetStatName(a1, a2); 
	}
	void CSteamUserStats002::GetStatType(CGameID a1, char  const* a2)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetStatType(a1, a2); 
	}
	int CSteamUserStats002::GetNumAchievements(CGameID a1)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetNumAchievements(a1); 
	}
	const char* CSteamUserStats002::GetAchievementName(CGameID a1, unsigned int a2)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetAchievementName(a1, a2); 
	}
	int CSteamUserStats002::RequestCurrentStats(CGameID a1)
	{
		if (g_bLogging) Logger->Write("%s (%u)\n", __FUNCTION__, a1.AppID()); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->RequestCurrentStats(a1); 
	}
	int CSteamUserStats002::GetStat(CGameID a1, char  const* a2, int * a3)
	{
		if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetStat(a1, a2, a3); 
	}
	int CSteamUserStats002::GetStat(CGameID a1, char  const* a2, float * a3)
	{
		if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetStat(a1, a2, a3); 
	}
	void CSteamUserStats002::SetStat(CGameID a1, char  const* a2, float a3)
	{
		if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->SetStat(a1, a2, a3); 
	}
	void CSteamUserStats002::SetStat(CGameID a1, char  const* a2, int a3)
	{
		if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->SetStat(a1, a2, a3); 
	}
	void CSteamUserStats002::UpdateAvgRateStat(CGameID a1, char  const* a2, float a3, double a4)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->UpdateAvgRateStat(a1, a2, a3, a4); 
	}
	bool CSteamUserStats002::GetAchievement(CGameID a1, char  const* a2, bool * a3)
	{
		if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetAchievement(a1, a2, a3); 
	}
	void CSteamUserStats002::SetAchievement(CGameID a1, char  const* a2)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->SetAchievement(a1, a2); 
	}
	void CSteamUserStats002::ClearAchievement(CGameID a1, char  const* a2)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->ClearAchievement(a1, a2); 
	}
	void CSteamUserStats002::StoreStats(CGameID a1)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->StoreStats(a1); 
	}
	void CSteamUserStats002::GetAchievementIcon(CGameID a1, char  const* a2)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetAchievementIcon(a1, a2); 
	}
	void CSteamUserStats002::GetAchievementDisplayAttribute(CGameID a1, char  const* a2, char  const* a3)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->GetAchievementDisplayAttribute(a1, a2, a3); 
	}
	void CSteamUserStats002::IndicateAchievementProgress(CGameID a1, char  const* a2, unsigned int a3, unsigned int a4)
	{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->IndicateAchievementProgress(a1, a2, a3, a4); 
	}
