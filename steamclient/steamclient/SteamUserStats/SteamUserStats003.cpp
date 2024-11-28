#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUserStats003.h"
#include ".\SteamUserStats.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUserStats* g_pSteamUserStats;

CSteamUserStats003::CSteamUserStats003()
{
}

CSteamUserStats003::~CSteamUserStats003()
{
}

int CSteamUserStats003::GetNumStats(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetNumStats(); 
}
void CSteamUserStats003::GetStatName(CGameID a1, unsigned int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetStatName(a1, a2); 
}
void CSteamUserStats003::GetStatType(CGameID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetStatType(a1, a2); 
}
int CSteamUserStats003::GetNumAchievements(CGameID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetNumAchievements(a1); 
}
const char* CSteamUserStats003::GetAchievementName(CGameID a1, unsigned int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetAchievementName(a1, a2); 
}
	int CSteamUserStats003::RequestCurrentStats(CGameID a1)
	{
		if (g_bLogging) Logger->Write("%s (%u)\n", __FUNCTION__, a1.AppID()); 
		g_pSteamUserStats = GSteamUserStats();
		return g_pSteamUserStats->RequestCurrentStats(a1); 
	}
int CSteamUserStats003::GetStat(CGameID a1, char  const* a2, int * a3)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetStat(a1, a2, a3); 
}
int CSteamUserStats003::GetStat(CGameID a1, char  const* a2, float * a3)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetStat(a1, a2, a3); 
}
void CSteamUserStats003::SetStat(CGameID a1, char  const* a2, int a3)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->SetStat(a1, a2, a3); 
}
void CSteamUserStats003::SetStat(CGameID a1, char  const* a2, float a3)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->SetStat(a1, a2, a3); 
}
void CSteamUserStats003::UpdateAvgRateStat(CGameID a1, char  const* a2, float a3, double a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->UpdateAvgRateStat(a1, a2, a3, a4); 
}
bool CSteamUserStats003::GetAchievement(CGameID a1, char  const* a2, bool * a3)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetAchievement(a1, a2, a3); 
}
void CSteamUserStats003::SetAchievement(CGameID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->SetAchievement(a1, a2); 
}
void CSteamUserStats003::ClearAchievement(CGameID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->ClearAchievement(a1, a2); 
}
void CSteamUserStats003::SetGroupAchievement(CGameID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->SetAchievement(a1, a2); 
}
void CSteamUserStats003::StoreStats(CGameID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->StoreStats(a1); 
}
void CSteamUserStats003::GetAchievementIcon(CGameID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetAchievementIcon(a1, a2); 
}
void CSteamUserStats003::GetAchievementDisplayAttribute(CGameID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->GetAchievementDisplayAttribute(a1, a2, a3); 
}
void CSteamUserStats003::IndicateAchievementProgress(CGameID a1, char  const* a2, unsigned int a3, unsigned int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUserStats = GSteamUserStats();
	return g_pSteamUserStats->IndicateAchievementProgress(a1, a2, a3, a4); 
}
