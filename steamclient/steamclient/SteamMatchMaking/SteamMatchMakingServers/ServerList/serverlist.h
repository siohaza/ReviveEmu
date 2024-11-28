#pragma once

#include "..\..\..\Common\utlvector.h"
#include "..\..\..\Common\utlrbtree.h"

#include "ServerManager.h"

#include "..\..\..\Common\steamtypes.h"
#include "..\..\matchmakinginterfaces.h"
#include "..\..\..\Common\vdf.h"

using namespace std;

struct query_t
{
	servernetadr_t addr;
	int serverID;
	float sendTime;
};

typedef enum
{
	NONE = 0,
	INFO_REQUESTED,
	INFO_RECEIVED
} QUERYSTATUS;

extern void v_strncpy(char *dest, const char *src, int bufsize);

class CServerManager;

struct TServer
{
	char chServerName[255];
	char chServerIPPort[24];
	unsigned long long ulLastPlayed;
};

class CServerList
{
public:
	CServerList(const CServerList &serverList, EMatchMakingType eType);
	~CServerList();

public:
	CUtlVector<servernetadr_t*>				m_RefreshList; // List of servers available for quick refresh

private:
	ISteamMatchmakingServerListResponse*	m_pResponseTarget; // Callback to notify the VGUI when we make some progress here
	//CUtlRBTree<query_t, unsigned short>		m_Queries; // We will store all currently active queries here
	CUtlVector<gameserveritem_t*>			m_Servers; // We will store processed valid servers here so we can pass them to the VGUI
	bool									m_bQuerying;	// Is refreshing taking place?
	char									m_chFilters[255]; // Filters to use when querying
	EMatchMakingType						m_Type; // Query type - internet, favorites, LAN, spectator, or friends
	//int										m_nMaxActive; // Maximum number of sockets to use when querying
	//int										m_nInvalidServers; // Number of servers marked as 'Do not refresh'
	int										m_nRefreshedServers; // Count of servers refreshed
	CServerManager*							m_pQuery; // Server query socket
	unsigned char							m_chRegion; // Server region to query
	int										m_iUpdateSerialNumber; // serial number of current update so we don't get results overlapping between different server list updates
	CRITICAL_SECTION						m_Critical;
	unsigned short							m_nAppID;

public:
	unsigned int		AddNewServer(gameserveritem_t * server, bool bAddToRefreshList = true);
	void				SetListParameters(unsigned int nAppID, EMatchMakingType eType, ISteamMatchmakingServerListResponse * target);
	bool				IsRefreshing(void);
	gameserveritem_t*	GetServer(unsigned int serverID);
	void				StopRefresh(void);
	void				StartRefresh(void);
	void				SetFilters(MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters);
	unsigned int		ServerCount(EMatchMakingType eType);
	const char*			GetFilters();
	void				ServerResponded(int serverID);
	void				RefreshComplete();
	void				RunFrame();
	bool				GetSingleServer(unsigned int nServerIP, unsigned short nServerPort, gameserveritem_t* serverItem);
	EMatchMakingType	GetType();
	void				GetServers(EMatchMakingType eType);
	void				PingServer(unsigned int a1, unsigned short a2, ISteamMatchmakingPingResponse * a3);
	void				PlayerDetails(unsigned int a1, unsigned short a2, ISteamMatchmakingPlayersResponse * a3);
	void				QuickRefresh();
	void				AddToFavorites(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 rTime32LastPlayedOnServer);
	void				RemoveFromFavorites(uint32 nAppID, uint32 nIP, uint16 nConnPort);
	void				StartRefreshLan();
	bool				GetFavoriteGame( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer );

private:
	void				GetRegionCodeToFilter(const char* szRegion);
	void				Clear(void);
	// VDF helper functions
	void				reindex(VdfKey * key, int keyIndex=1);
	VdfKey*				createNewKey(char * name=0, char * value=0);
	char*				copyStr(char * str);
	VdfKey*				createNewFavoriteTree(char * index, char * name,char * address, char * lastPlayed, char * appId);
	VdfKey*				DefaultVdfFile();
};