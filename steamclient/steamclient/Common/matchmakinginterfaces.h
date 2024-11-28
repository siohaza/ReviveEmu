#pragma once

#include "matchmakingtypes.h"

class ISteamMatchmakingServerListResponse
{
public:
	virtual void ServerResponded(int iServer) = 0;
	virtual void ServerFailedToRespond(int iServer) = 0;
	virtual void ServerRefreshComplete(EMatchMakingServerResponse response) = 0;
};

class ISteamMatchmakingPingResponse
{
public:
	virtual void ServerResponded( gameserveritem_t &server ) = 0;
	virtual void ServerFailedToRespond() = 0;
};

class ISteamMatchmakingPlayersResponse
{
public:
	virtual void AddPlayerToList( const char *pchName, int nScore, float flTimePlayed ) = 0;
	virtual void PlayersFailedToRespond() = 0;
	virtual void PlayersRefreshComplete() = 0;
};

class ISteamMatchmakingRulesResponse
{
public:
	virtual void RulesResponded( const char *pchRule, const char *pchValue ) = 0;
	virtual void RulesFailedToRespond() = 0;
	virtual void RulesRefreshComplete() = 0;
};