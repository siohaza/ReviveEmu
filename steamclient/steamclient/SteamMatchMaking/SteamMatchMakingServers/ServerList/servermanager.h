#pragma once
#define _CRT_SECURE_NO_WARNINGS 1	//Delete this later
#pragma comment(lib, "wsock32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <process.h>
//#include "Steam/tier0/memalloc.h"
#include "..\..\..\Common\utlvector.h"
#include <vector>
#include "..\..\..\Common\steamtypes.h"
#include "..\..\matchmakingtypes.h"
#include "..\..\matchmakinginterfaces.h"
#include <string>
#include ".\ServerInfo.h"
#include ".\ServerMaster.h"
#include ".\ServerList.h"
#include ".\ServerLan.h"

#define NET_UDP_RECVSIZE		8192
#define MAX_THREADS				200

#pragma pack(push)	// Change alignment
#pragma pack(1) 

	struct TMasterReply {
		byte			bytOctet1;		// First IP octet.
		byte			bytOctet2;		// Second IP octet.
		byte			bytOctet3;		// Third IP octet.
		byte			bytOctet4;		// Fourth IP octet.
		unsigned short	sPort;			// Server Port
	};

	struct TMasterRequest {
		byte			bytRegionCode;
		char			szMasterServer[MAX_PATH];
		unsigned short	sMasterPort;
		char			szIPIterator[MAX_PATH];
		char			szFilter[MAX_PATH];
	};

	struct TServerIP {
		char			szIP[16];
		unsigned short	sPort;
	};

	struct TServerHandle {
		bool			bAllowRefresh;
		char			szIP[19];
		unsigned short	sPort;
	};
#pragma pack(pop)

// Exception Handler
int exceptionhandler(unsigned int code, struct _EXCEPTION_POINTERS * ep);

class CServerList;

class CServerManager
{
private:
	TServerHandle * m_pServerHandle;
	CServerList* m_pServerList;

public:
	CRITICAL_SECTION m_gCritical;
	CUtlVector<gameserveritem_t*> m_vecRefreshed;
	CUtlVector<TServerIP*> m_vecServer;
	CUtlVector<TServerIP*> m_vecQuick;
	unsigned int m_uActiveThreads;
	bool m_bIsDownloading;
	bool m_bIsRefresh;
	bool m_bIsQuick;

public:
	CServerManager(CServerList*);
	~CServerManager(void);

private:
	TServerHandle * GetFirstServer();
	bool			GetNextServer(TServerHandle * pHandle);
	TServerHandle * GetCloseServer(TServerHandle * pHandle);

public:
	void ServerIterator();

public:
	static bool SetConnectionInfo(SOCKADDR_IN &sckAddrIn, 
		const char * cszAddress, 
		short sPort);

	void PingServer(unsigned int uAddr, 
		unsigned short sPort, 
		ISteamMatchmakingPingResponse * pResponse);

	void PlayerDetails(unsigned int uAddr, 
		unsigned short sPort, 
		ISteamMatchmakingPlayersResponse * pResponse);

	bool StartRefreshFavorites();
	bool StartRefresh(TMasterRequest * pRequest, bool bQuick = false);
	bool StartRefreshLan(unsigned short uAppId);
	bool StopRefresh();
	void RunFrame();
	void Clear();
};