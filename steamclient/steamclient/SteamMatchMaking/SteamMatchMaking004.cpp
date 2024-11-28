#include "..\Common\commonincludes.h"
#include ".\SteamMatchMaking004.h"
#include ".\SteamMatchMaking.h"
#include ".\matchmakingtypes.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamMatchMaking* g_pSteamMatchMaking;

CSteamMatchMaking004::CSteamMatchMaking004()
{
}

CSteamMatchMaking004::~CSteamMatchMaking004()
{
}

int CSteamMatchMaking004::GetFavoriteGameCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGameCount(); 
}
bool CSteamMatchMaking004::GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGame(a1, a2, a3, a4, a5, a6, a7); 
}
int CSteamMatchMaking004::AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->AddFavoriteGame(a1, a2, a3, a4, a5, a6); 
}
bool CSteamMatchMaking004::RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RemoveFavoriteGame(a1, a2, a3, a4); 
}
void CSteamMatchMaking004::RequestLobbyList(unsigned long long a1, MatchMakingKeyValuePair_t * a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RequestLobbyList(a1, a2, a3); 
}
CSteamID CSteamMatchMaking004::GetLobbyByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyByIndex(a1); 
}
void CSteamMatchMaking004::CreateLobby(unsigned long long a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->CreateLobby(a1, a2); 
}
void CSteamMatchMaking004::JoinLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->JoinLobby(a1); 
}
void CSteamMatchMaking004::LeaveLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->LeaveLobby(a1); 
}
bool CSteamMatchMaking004::InviteUserToLobby(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->InviteUserToLobby(a1, a2); 
}
int CSteamMatchMaking004::GetNumLobbyMembers(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetNumLobbyMembers(a1); 
}
CSteamID CSteamMatchMaking004::GetLobbyMemberByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberByIndex(a1, a2); 
}
const char* CSteamMatchMaking004::GetLobbyData(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyData(a1, a2); 
}
void CSteamMatchMaking004::SetLobbyData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyData(a1, a2, a3); 
}
const char* CSteamMatchMaking004::GetLobbyMemberData(CSteamID a1, CSteamID a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberData(a1, a2, a3); 
}
void CSteamMatchMaking004::SetLobbyMemberData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyMemberData(a1, a2, a3); 
}
bool CSteamMatchMaking004::SendLobbyChatMsg(CSteamID a1, void  const* a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SendLobbyChatMsg(a1, a2, a3); 
}
int CSteamMatchMaking004::GetLobbyChatEntry(CSteamID a1, int a2, CSteamID* a3, void * a4, int a5, EChatEntryType * a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyChatEntry(a1, a2, a3, a4, a5, a6); 
}

void CSteamMatchMaking004::RequestLobbyData(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking004::SetLobbyGameServer(CSteamID a1, unsigned int a2, unsigned short a3, CSteamID a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking004::AddRequestLobbyListFilter(const char *a1, const char *a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking004::AddRequestLobbyListNumericalFilter(const char *a1, int a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking004::AddRequestLobbyListSlotsAvailableFilter()
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking004::GetLobbyGameServer(CSteamID a1, unsigned int *a2, unsigned short *a3, CSteamID *a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking004::GetLobbyMemberLimit(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking004::SetLobbyMemberLimit(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking004::RequestFriendsLobbies()
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}