#include ".\SteamMatchMakingServers.h"

class CSteamMatchMakingServers001
{
public:
	CSteamMatchMakingServers001();
	~CSteamMatchMakingServers001();

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
};