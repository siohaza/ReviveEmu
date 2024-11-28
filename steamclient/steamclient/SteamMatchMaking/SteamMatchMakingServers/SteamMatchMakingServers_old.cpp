#include ".\SteamMatchMakingServers.h"
#include "..\matchmakingtypes.h"
#include "..\..\Common\support.h"

char chProcName[255];

CSteamMatchMakingServers::CSteamMatchMakingServers()
{
		m_bIsGoldsrc = false;
		m_eActiveType = eInvalidServer;
		GetModuleFileNameA(NULL, chProcName, MAX_PATH);
		if(_stristr(chProcName, "hl.exe")) m_bIsGoldsrc = true;
}

CSteamMatchMakingServers::~CSteamMatchMakingServers()
{
	for (int idx = 0; idx < 6; idx++)
	{
		if (m_pServerList[idx])
		{
			delete m_pServerList[idx];
		}
	}
}

void CSteamMatchMakingServers::RequestInternetServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	if (m_bIsGoldsrc)
	{
		m_iAppId = iApp;
		m_eActiveType = eInvalidServer;
		pRequestServersResponse->ServerResponded(1);
		return;
	}
	
	m_eActiveType = eInternetServer;

	// Check to see if the list exists for this type of servers. If not, create a new instance.
	if (!m_pServerList[m_eActiveType])
	{
		m_pServerList[m_eActiveType] = new CServerList(*m_pServerList[m_eActiveType], m_eActiveType);
	}

	// Make sure to tell our list about a callback it should process
	m_pServerList[m_eActiveType]->SetListParameters(iApp, m_eActiveType, pRequestServersResponse);
	
	// Process filters as passed from the VGUI
	if (ppchFilters && nFilters) 
			m_pServerList[m_eActiveType]->SetFilters(ppchFilters, nFilters);
	
	// Go go go!!!
	if (iApp != 0)
	{
		this->Refresh();
	}
}

void CSteamMatchMakingServers::RequestLANServerList(unsigned int a1, ISteamMatchmakingServerListResponse * a2)
{
	if (m_bIsGoldsrc)
	{
		m_eActiveType = eInvalidServer;
		a2->ServerResponded(1);
		return;
	}
	m_eActiveType = eLANServer;

	if (!m_pServerList[m_eActiveType])
	{
		m_pServerList[m_eActiveType] = new CServerList(*m_pServerList[m_eActiveType], m_eActiveType);
	}

	m_pServerList[m_eActiveType]->SetListParameters(a1, m_eActiveType, a2);

	//m_pServerList[m_eActiveType]->StartRefreshLan(a1);
	m_pServerList[m_eActiveType]->StartRefreshLan();
}
void CSteamMatchMakingServers::RequestFriendsServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	if (m_bIsGoldsrc)
	{
		m_eActiveType = eInvalidServer;
		m_iAppId = iApp;
		pRequestServersResponse->ServerResponded(1);
		return;
	}
	m_eActiveType = eFriendsServer;

	if (!m_pServerList[m_eActiveType])
	{
		m_pServerList[m_eActiveType] = new CServerList(*m_pServerList[m_eActiveType], m_eActiveType);
	}

	// Make sure to tell our list about a callback it should process
	m_pServerList[m_eActiveType]->SetListParameters(iApp, m_eActiveType, pRequestServersResponse);
}
void CSteamMatchMakingServers::RequestFavoritesServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	if (m_bIsGoldsrc)
	{
		m_iAppId = iApp;
		m_eActiveType = eInvalidServer;
		pRequestServersResponse->ServerResponded(1);
		return;
	}
	m_eActiveType = eFavoritesServer;

	if (!m_pServerList[m_eActiveType])
	{
		m_pServerList[m_eActiveType] = new CServerList(*m_pServerList[m_eActiveType], m_eActiveType);
	}

	// Make sure to tell our list about a callback it should process
	m_pServerList[m_eActiveType]->SetListParameters(iApp, m_eActiveType, pRequestServersResponse);

	// Process filters as passed from the VGUI
	if (ppchFilters && nFilters) 
		m_pServerList[m_eActiveType]->SetFilters(ppchFilters, nFilters);

	// Go go go!!!
	if (iApp != 0) 
		m_pServerList[m_eActiveType]->GetServers(m_eActiveType);
}
void CSteamMatchMakingServers::RequestHistoryServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	if (m_bIsGoldsrc)
	{
		m_eActiveType = eInvalidServer;
		m_iAppId = iApp;
		pRequestServersResponse->ServerResponded(1);
		return;
	}
	m_eActiveType = eHistoryServer;

	if (!m_pServerList[m_eActiveType])
	{
		m_pServerList[m_eActiveType] = new CServerList(*m_pServerList[m_eActiveType], m_eActiveType);
	}
	// Make sure to tell our list about a callback it should process
	m_pServerList[m_eActiveType]->SetListParameters(iApp, m_eActiveType, pRequestServersResponse);

	// Process filters as passed from the VGUI
	if (ppchFilters && nFilters) 
		m_pServerList[m_eActiveType]->SetFilters(ppchFilters, nFilters);

	// Go go go!!!
	if (iApp != 0) 
		m_pServerList[m_eActiveType]->GetServers(m_eActiveType);

}
void CSteamMatchMakingServers::RequestSpectatorServerList(uint32 iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	if (m_bIsGoldsrc)
	{
		m_eActiveType = eInvalidServer;
		m_iAppId = iApp;
		pRequestServersResponse->ServerResponded(1);
		return;
	}
	m_eActiveType = eSpectatorServer;

	if (!m_pServerList[m_eActiveType])
	{
		m_pServerList[m_eActiveType] = new CServerList(*m_pServerList[m_eActiveType], m_eActiveType);
	}

	m_pServerList[m_eActiveType]->SetListParameters(iApp, m_eActiveType, pRequestServersResponse);
	if (ppchFilters && nFilters) 
			m_pServerList[m_eActiveType]->SetFilters(ppchFilters, nFilters);
	
	if (iApp != 0)
	{
		this->Refresh();
	}
}
gameserveritem_t* CSteamMatchMakingServers::GetServerDetails( EMatchMakingType eType, int iServer )
{
	if (m_bIsGoldsrc)
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
	if (m_eActiveType != eInvalidServer)
		return m_pServerList[m_eActiveType]->GetServer(iServer);

}
void CSteamMatchMakingServers::CancelQuery(EMatchMakingType a1)
{
	if (a1 == eInvalidServer || m_eActiveType == eInvalidServer) return;
	this->m_pServerList[m_eActiveType]->StopRefresh();
}
void CSteamMatchMakingServers::RefreshQuery(EMatchMakingType a1)
{
	if (a1 == eInvalidServer || m_eActiveType == eInvalidServer) return;
	this->m_pServerList[m_eActiveType]->QuickRefresh();
}
bool CSteamMatchMakingServers::IsRefreshing(EMatchMakingType a1)
{
	if (a1 != eInvalidServer && m_eActiveType != eInvalidServer) 
	{
		if (m_pServerList[m_eActiveType])
		{
			return this->m_pServerList[m_eActiveType]->IsRefreshing();
		}
	}
	return false;
}
int CSteamMatchMakingServers::GetServerCount(EMatchMakingType a1)
{
	m_eActiveType = a1;
	if (!m_pServerList[a1])
	{
		m_pServerList[a1] = new CServerList(*m_pServerList[a1], m_eActiveType);
	}
	return m_pServerList[m_eActiveType]->ServerCount(a1);
}
void CSteamMatchMakingServers::RefreshServer(EMatchMakingType a1, int a2)
{
}
void CSteamMatchMakingServers::PingServer(unsigned int a1, unsigned short a2, ISteamMatchmakingPingResponse * a3)
{
	if (m_eActiveType != eInvalidServer)
		m_pServerList[m_eActiveType]->PingServer(a1, a2, a3);
}

void CSteamMatchMakingServers::PlayerDetails(unsigned int a1, unsigned short a2, ISteamMatchmakingPlayersResponse * a3)
{
	if (m_eActiveType != eInvalidServer)
		m_pServerList[m_eActiveType]->PlayerDetails(a1, a2, a3);
}

void CSteamMatchMakingServers::ServerRules(unsigned int a1, unsigned short a2, ISteamMatchmakingRulesResponse * a3)
{
}

void CSteamMatchMakingServers::CancelServerQuery(int a1)
{
}

void CSteamMatchMakingServers::Refresh()
{
	if (m_eActiveType != eInvalidServer)
		m_pServerList[m_eActiveType]->StartRefresh();
}

void CSteamMatchMakingServers::RunFrame()
{
	if (m_eActiveType != eInvalidServer) m_pServerList[m_eActiveType]->RunFrame();
}

EMatchMakingType CSteamMatchMakingServers::GetActiveType()
{
	return m_eActiveType;
}

int CSteamMatchMakingServers::AddToFavorites(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 rTime32LastPlayedOnServer)
{
	if (nAppID)
	{
		m_eActiveType = eFavoritesServer;
	}
	else
		m_eActiveType = eHistoryServer;

	m_pServerList[m_eActiveType]->AddToFavorites(nAppID, nIP, nConnPort, rTime32LastPlayedOnServer);
	m_eActiveType = eInvalidServer;
	return 1;
}

bool CSteamMatchMakingServers::RemoveFromFavorites(uint32 nAppID, uint32 nIP, uint16 nConnPort)
{
	m_eActiveType = eFavoritesServer;
	m_pServerList[m_eActiveType]->RemoveFromFavorites(nAppID, nIP, nConnPort);
	return 1;
}

bool CSteamMatchMakingServers::GetFavoriteGame( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer )
{
	m_eActiveType = eFavoritesServer;
	return m_pServerList[m_eActiveType]->GetFavoriteGame( iGame, pnAppID, pnIP, pnConnPort, pnQueryPort, punFlags, pRTime32LastPlayedOnServer );
}

CSteamMatchMakingServers* g_pSteamMatchMakingServers;

CSteamMatchMakingServers* GSteamMatchMakingServers()
{
	static CSteamMatchMakingServers g_SteamMatchMakingServers;
	return &g_SteamMatchMakingServers;
}