#include ".\SteamMatchMakingServers.h"
#include "..\matchmakingtypes.h"

CSteamMatchMakingServers::CSteamMatchMakingServers()
{
}

CSteamMatchMakingServers::~CSteamMatchMakingServers()
{
}

void CSteamMatchMakingServers::RequestInternetServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
}

void CSteamMatchMakingServers::RequestLANServerList(unsigned int a1, ISteamMatchmakingServerListResponse * a2)
{
}

void CSteamMatchMakingServers::RequestFriendsServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
}

void CSteamMatchMakingServers::RequestFavoritesServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
}

void CSteamMatchMakingServers::RequestHistoryServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
}

void CSteamMatchMakingServers::RequestSpectatorServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
}

gameserveritem_t* CSteamMatchMakingServers::GetServerDetails( EMatchMakingType eType, int iServer )
{
		static gameserveritem_t test;
		servernetadr_t adr;
		adr.Init(0xFFFFFFFF, 1337, 1337);
		test.SetName("SERVERBROWSER DISABLED");
		test.m_bDoNotRefresh = 1;
		test.m_bHadSuccessfulResponse = 1;
		test.m_bPassword = 1;
		test.m_bSecure = 1;
		test.m_nAppID = m_iAppId;
		test.m_nBotPlayers  = 0;
		test.m_NetAdr = adr;
		test.m_nMaxPlayers = 32;
		test.m_nPing = 5;
		test.m_nPlayers = 30;
		test.m_nServerVersion = 1337;
		strcpy(test.m_szGameDescription, "REVOLUTiON");
		strcpy(test.m_szGameDir, "cstrike");
		strcpy(test.m_szGameTags, "");
		strcpy(test.m_szMap, "coming_soon");
		test.m_ulTimeLastPlayed = 0;
		return &test;
}
void CSteamMatchMakingServers::CancelQuery(EMatchMakingType a1)
{
}

void CSteamMatchMakingServers::RefreshQuery(EMatchMakingType a1)
{
}

bool CSteamMatchMakingServers::IsRefreshing(EMatchMakingType a1)
{
	return true;
}

int CSteamMatchMakingServers::GetServerCount(EMatchMakingType a1)
{
	return 0;
}

void CSteamMatchMakingServers::RefreshServer(EMatchMakingType a1, int a2)
{
}
void CSteamMatchMakingServers::PingServer(unsigned int a1, unsigned short a2, ISteamMatchmakingPingResponse * a3)
{
}

void CSteamMatchMakingServers::PlayerDetails(unsigned int a1, unsigned short a2, ISteamMatchmakingPlayersResponse * a3)
{
}

void CSteamMatchMakingServers::ServerRules(unsigned int a1, unsigned short a2, ISteamMatchmakingRulesResponse * a3)
{
}

void CSteamMatchMakingServers::CancelServerQuery(int a1)
{
}

void CSteamMatchMakingServers::Refresh()
{
}

void CSteamMatchMakingServers::RunFrame()
{
}

EMatchMakingType CSteamMatchMakingServers::GetActiveType()
{
	return eInvalidServer;
}

int CSteamMatchMakingServers::AddToFavorites(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 rTime32LastPlayedOnServer)
{
	return 1;
}

bool CSteamMatchMakingServers::RemoveFromFavorites(uint32 nAppID, uint32 nIP, uint16 nConnPort)
{
	return 1;
}

bool CSteamMatchMakingServers::GetFavoriteGame( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer )
{
	return 1;
}

CSteamMatchMakingServers* g_pSteamMatchMakingServers;

CSteamMatchMakingServers* GSteamMatchMakingServers()
{
	static CSteamMatchMakingServers g_SteamMatchMakingServers;
	return &g_SteamMatchMakingServers;
}