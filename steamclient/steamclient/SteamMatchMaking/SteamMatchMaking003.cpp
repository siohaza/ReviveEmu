#include "..\Common\commonincludes.h"
#include ".\SteamMatchMaking003.h"
#include ".\SteamMatchMaking.h"
#include ".\matchmakingtypes.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamMatchMaking* g_pSteamMatchMaking;

CSteamMatchMaking003::CSteamMatchMaking003()
{
}

CSteamMatchMaking003::~CSteamMatchMaking003()
{
}

int CSteamMatchMaking003::GetFavoriteGameCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGameCount(); 
}
bool CSteamMatchMaking003::GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGame(a1, a2, a3, a4, a5, a6, a7); 
}
int CSteamMatchMaking003::AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->AddFavoriteGame(a1, a2, a3, a4, a5, a6); 
}
bool CSteamMatchMaking003::RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RemoveFavoriteGame(a1, a2, a3, a4); 
}
void CSteamMatchMaking003::RequestLobbyList(unsigned long long a1, MatchMakingKeyValuePair_t * a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RequestLobbyList(a1, a2, a3); 
}
CSteamID CSteamMatchMaking003::GetLobbyByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyByIndex(a1); 
}
void CSteamMatchMaking003::CreateLobby(unsigned long long a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->CreateLobby(a1, a2); 
}
void CSteamMatchMaking003::JoinLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->JoinLobby(a1); 
}
void CSteamMatchMaking003::LeaveLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->LeaveLobby(a1); 
}
bool CSteamMatchMaking003::InviteUserToLobby(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->InviteUserToLobby(a1, a2); 
}
int CSteamMatchMaking003::GetNumLobbyMembers(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetNumLobbyMembers(a1); 
}
CSteamID CSteamMatchMaking003::GetLobbyMemberByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberByIndex(a1, a2); 
}
const char* CSteamMatchMaking003::GetLobbyData(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyData(a1, a2); 
}
void CSteamMatchMaking003::SetLobbyData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyData(a1, a2, a3); 
}
const char* CSteamMatchMaking003::GetLobbyMemberData(CSteamID a1, CSteamID a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberData(a1, a2, a3); 
}
void CSteamMatchMaking003::SetLobbyMemberData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyMemberData(a1, a2, a3); 
}
bool CSteamMatchMaking003::SendLobbyChatMsg(CSteamID a1, void  const* a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SendLobbyChatMsg(a1, a2, a3); 
}
int CSteamMatchMaking003::GetLobbyChatEntry(CSteamID a1, int a2, CSteamID* a3, void * a4, int a5, EChatEntryType * a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyChatEntry(a1, a2, a3, a4, a5, a6); 
}

void CSteamMatchMaking003::RequestLobbyData(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::SetLobbyGameServer(CSteamID a1, unsigned int a2, unsigned short a3, CSteamID a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::AddRequestLobbyListFilter(const char *a1, const char *a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::AddRequestLobbyListNumericalFilter(const char *a1, int a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::AddRequestLobbyListSlotsAvailableFilter()
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::GetLobbyGameServer(CSteamID a1, unsigned int *a2, unsigned short *a3, CSteamID *a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::GetLobbyMemberLimit(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::SetLobbyMemberLimit(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::RequestFriendsLobbies()
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking003::SetLobbyVoiceEnabled(CSteamID a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}