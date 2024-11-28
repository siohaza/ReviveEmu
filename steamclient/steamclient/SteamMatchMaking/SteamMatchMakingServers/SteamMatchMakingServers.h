#pragma once

#include "..\matchmakingtypes.h"
#include "..\matchmakinginterfaces.h"
#include ".\ServerList\ServerList.h"

class CSteamMatchMakingServers
{
public:
	CSteamMatchMakingServers();
	~CSteamMatchMakingServers();

	virtual void RequestInternetServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4);
	virtual void RequestLANServerList(unsigned int a1, ISteamMatchmakingServerListResponse * a2);
	virtual void RequestFriendsServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4);
	virtual void RequestFavoritesServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4);
	virtual void RequestHistoryServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4);
	virtual void RequestSpectatorServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4);
	virtual gameserveritem_t* GetServerDetails(EMatchMakingType a1, int a2);
	virtual void CancelQuery(EMatchMakingType a1);
	virtual void RefreshQuery(EMatchMakingType a1);
	virtual bool IsRefreshing(EMatchMakingType a1);
	virtual int GetServerCount(EMatchMakingType a1);
	virtual void RefreshServer(EMatchMakingType a1, int a2);
	virtual void PingServer(unsigned int a1, unsigned short a2, ISteamMatchmakingPingResponse * a3);
	virtual void PlayerDetails(unsigned int a1, unsigned short a2, ISteamMatchmakingPlayersResponse * a3);
	virtual void ServerRules(unsigned int a1, unsigned short a2, ISteamMatchmakingRulesResponse * a3);
	virtual void CancelServerQuery(int a1);

	//helper functions, added by us, they have got nothing to do with steam/game interface
	virtual int AddToFavorites(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 rTime32LastPlayedOnServer);
	virtual bool RemoveFromFavorites(uint32 nAppID, uint32 nIP, uint16 nConnPort);
	virtual bool GetFavoriteGame( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer );
	virtual void Refresh();
	virtual EMatchMakingType GetActiveType();
	virtual void RunFrame();

private:
	EMatchMakingType m_eActiveType;
	CServerList* m_pServerList[6];
	bool m_bIsGoldsrc;
	int m_iAppId;
};

 CSteamMatchMakingServers* GSteamMatchMakingServers();