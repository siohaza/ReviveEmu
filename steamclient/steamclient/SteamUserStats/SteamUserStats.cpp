#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include "..\Common\steamtypes.h"
#include ".\SteamUserStats.h"
#include <vector>

//-----------------------------------------------------------------------------
// Purpose: called when the latests stats and achievements have been received
//			from the server
//-----------------------------------------------------------------------------
struct UserStatsReceived_t
{
	enum { k_iCallback = k_iSteamUserStatsCallbacks + 1 };
	uint64		m_nGameID;		// Game these stats are for
	EResult		m_eResult;		// Success / error fetching the stats
};


//-----------------------------------------------------------------------------
// Purpose: result of a request to store the user stats for a game
//-----------------------------------------------------------------------------
struct UserStatsStored_t
{
	enum { k_iCallback = k_iSteamUserStatsCallbacks + 2 };
	uint64		m_nGameID;		// Game these stats are for
	EResult		m_eResult;		// success / error
};

//-----------------------------------------------------------------------------
// Purpose: result of a request to store the achievements for a game, or an 
//			"indicate progress" call. If both m_nCurProgress and m_nMaxProgress
//			are zero, that means the achievement has been fully unlocked.
//-----------------------------------------------------------------------------
struct UserAchievementStored_t
{
	enum { k_iCallback = k_iSteamUserStatsCallbacks + 3 };

	uint64		m_nGameID;				// Game this is for
	bool		m_bGroupAchievement;	// if this is a "group" achievement
	char		m_rgchAchievementName[128];		// name of the achievement
	uint32		m_nCurProgress;			// current progress towards the achievement
	uint32		m_nMaxProgress;			// "out of" this many
};

CSteamUserStats* g_pSteamUserStats;

CSteamUserStats* GSteamUserStats()
{
	static CSteamUserStats g_SteamUserStats;
	return &g_SteamUserStats;
}

CSteamUserStats::CSteamUserStats()
{
}

CSteamUserStats::~CSteamUserStats()
{
}

extern std::vector<CallbackMsg_t*> g_CallbackMsgList;

int CSteamUserStats::GetNumStats(CGameID a1)
{
	return 0;
}

int CSteamUserStats::GetNumStats(void)
{
	return 0;
}

void CSteamUserStats::GetStatName(CGameID a1, unsigned int a2)
{
}
void CSteamUserStats::GetStatType(CGameID a1, char  const* a2)
{
}
int CSteamUserStats::GetNumAchievements(CGameID a1)
{
	return 0;
}
const char* CSteamUserStats::GetAchievementName(CGameID a1, unsigned int a2)
{
	return "dummy";
}
int CSteamUserStats::RequestCurrentStats(CGameID a1)
{		
	UserStatsReceived_t* userstats = new UserStatsReceived_t;
	userstats->m_eResult = k_EResultOK;
	userstats->m_nGameID = a1.ToUint64();
	
	CallbackMsg_t* callbackmsg = new CallbackMsg_t;
	callbackmsg->m_hSteamUser = 1;
	callbackmsg->m_iCallback = k_iSteamUserStatsCallbacks + 1;
	callbackmsg->m_pubParam = (void*)userstats;
	callbackmsg->m_cubParam = sizeof(UserStatsReceived_t);
	g_CallbackMsgList.push_back(callbackmsg);

	return 1;
}
int CSteamUserStats::GetStat(CGameID a1, char  const* a2, int * a3)
{
	return 0;
	*a3 = 0;
}
int CSteamUserStats::GetStat(CGameID a1, char  const* a2, float * a3)
{
	return 0;
	*a3 = 0;
}
void CSteamUserStats::SetStat(CGameID a1, char  const* a2, int a3)
{
}
void CSteamUserStats::SetStat(CGameID a1, char  const* a2, float a3)
{
}
void CSteamUserStats::UpdateAvgRateStat(CGameID a1, char  const* a2, float a3, double a4)
{
}
bool CSteamUserStats::GetAchievement( CGameID nGameID, const char *pchName, bool *pbAchieved )
{
	*pbAchieved = 1;
	return 1;
}
void CSteamUserStats::SetAchievement(CGameID a1, char  const* a2)
{
}
void CSteamUserStats::ClearAchievement(CGameID a1, char  const* a2)
{
}
void CSteamUserStats::StoreStats(CGameID a1)
{
}
void CSteamUserStats::GetAchievementIcon(CGameID a1, char  const* a2)
{
}
void CSteamUserStats::GetAchievementDisplayAttribute(CGameID a1, char  const* a2, char  const* a3)
{
}
void CSteamUserStats::IndicateAchievementProgress(CGameID a1, char  const* a2, unsigned int a3, unsigned int a4)
{
}

int CSteamUserStats::GetNumGroupAchievements(CGameID a1)
{
	return 0;
}

void CSteamUserStats::GetGroupAchievementName(CGameID a1, unsigned int a2)
{
}

bool CSteamUserStats::GetGroupAchievement(CGameID a1, const char *a2, bool *a3)
{
	*a3 = 0;
	return 0;
}

void CSteamUserStats::SetGroupAchievement(CGameID a1, const char *a2)
{
}

void CSteamUserStats::ClearGroupAchievement(CGameID a1, const char *a2)
{
}