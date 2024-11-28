#include "..\..\Common\commonincludes.h"
#include ".\SteamMatchMakingServers001.h"
#include ".\SteamMatchMakingServers.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamMatchMakingServers* g_pSteamMatchMakingServers;

CSteamMatchMakingServers001::CSteamMatchMakingServers001()
{
}

CSteamMatchMakingServers001::~CSteamMatchMakingServers001()
{
}

void CSteamMatchMakingServers001::RequestInternetServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4)
{
	MatchMakingKeyValuePair_t *test;
	test = *a2;
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->RequestInternetServerList(a1, a2, a3, a4); 
}
void CSteamMatchMakingServers001::RequestLANServerList(unsigned int a1, ISteamMatchmakingServerListResponse * a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->RequestLANServerList(a1, a2); 
}
void CSteamMatchMakingServers001::RequestFriendsServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->RequestFriendsServerList(a1, a2, a3, a4); 
}
void CSteamMatchMakingServers001::RequestFavoritesServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4)
{
	MatchMakingKeyValuePair_t *test;
	test = *a2;
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->RequestFavoritesServerList(a1, a2, a3, a4); 
}
void CSteamMatchMakingServers001::RequestHistoryServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->RequestHistoryServerList(a1, a2, a3, a4); 
}
void CSteamMatchMakingServers001::RequestSpectatorServerList(unsigned int a1, MatchMakingKeyValuePair_t ** a2, unsigned int a3, ISteamMatchmakingServerListResponse * a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->RequestSpectatorServerList(a1, a2, a3, a4); 
}
gameserveritem_t* CSteamMatchMakingServers001::GetServerDetails(EMatchMakingType a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->GetServerDetails(a1, a2); 
}
void CSteamMatchMakingServers001::CancelQuery(EMatchMakingType a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->CancelQuery(a1); 
}
void CSteamMatchMakingServers001::RefreshQuery(EMatchMakingType a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->RefreshQuery(a1); 
}
bool CSteamMatchMakingServers001::IsRefreshing(EMatchMakingType a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->IsRefreshing(a1); 
}
int CSteamMatchMakingServers001::GetServerCount(EMatchMakingType a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->GetServerCount(a1); 
}
void CSteamMatchMakingServers001::RefreshServer(EMatchMakingType a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->RefreshServer(a1, a2); 
}
void CSteamMatchMakingServers001::PingServer(unsigned int a1, unsigned short a2, ISteamMatchmakingPingResponse * a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->PingServer(a1, a2, a3); 
}
void CSteamMatchMakingServers001::PlayerDetails(unsigned int a1, unsigned short a2, ISteamMatchmakingPlayersResponse * a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->PlayerDetails(a1, a2, a3); 
}
void CSteamMatchMakingServers001::ServerRules(unsigned int a1, unsigned short a2, ISteamMatchmakingRulesResponse * a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->ServerRules(a1, a2, a3); 
}
void CSteamMatchMakingServers001::CancelServerQuery(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->CancelServerQuery(a1); 
}
