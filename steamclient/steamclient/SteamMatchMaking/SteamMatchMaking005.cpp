#include "..\Common\commonincludes.h"
#include ".\SteamMatchMaking005.h"
#include ".\SteamMatchMaking.h"
#include ".\matchmakingtypes.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamMatchMaking* g_pSteamMatchMaking;

CSteamMatchMaking005::CSteamMatchMaking005()
{
}

CSteamMatchMaking005::~CSteamMatchMaking005()
{
}

int CSteamMatchMaking005::GetFavoriteGameCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGameCount(); 
}
bool CSteamMatchMaking005::GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGame(a1, a2, a3, a4, a5, a6, a7); 
}
int CSteamMatchMaking005::AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->AddFavoriteGame(a1, a2, a3, a4, a5, a6); 
}
bool CSteamMatchMaking005::RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RemoveFavoriteGame(a1, a2, a3, a4); 
}
int CSteamMatchMaking005::RequestLobbyList()
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RequestLobbyList(); 
}
CSteamID CSteamMatchMaking005::GetLobbyByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyByIndex(a1); 
}
void CSteamMatchMaking005::CreateLobby(int eLobbyType)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->CreateLobby(eLobbyType); 
}
void CSteamMatchMaking005::JoinLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->JoinLobby(a1); 
}
void CSteamMatchMaking005::LeaveLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->LeaveLobby(a1); 
}
bool CSteamMatchMaking005::InviteUserToLobby(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->InviteUserToLobby(a1, a2); 
}
int CSteamMatchMaking005::GetNumLobbyMembers(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetNumLobbyMembers(a1); 
}
CSteamID CSteamMatchMaking005::GetLobbyMemberByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberByIndex(a1, a2); 
}
const char* CSteamMatchMaking005::GetLobbyData(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyData(a1, a2); 
}
void CSteamMatchMaking005::SetLobbyData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s (%s, %s)\n", __FUNCTION__, a2, a3); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyData(a1, a2, a3); 
}
const char* CSteamMatchMaking005::GetLobbyMemberData(CSteamID a1, CSteamID a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberData(a1, a2, a3); 
}
void CSteamMatchMaking005::SetLobbyMemberData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyMemberData(a1, a2, a3); 
}
bool CSteamMatchMaking005::SendLobbyChatMsg(CSteamID a1, void  const* a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SendLobbyChatMsg(a1, a2, a3); 
}
int CSteamMatchMaking005::GetLobbyChatEntry(CSteamID a1, int a2, CSteamID* a3, void * a4, int a5, EChatEntryType * a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyChatEntry(a1, a2, a3, a4, a5, a6); 
}

void CSteamMatchMaking005::RequestLobbyData(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking005::SetLobbyGameServer(CSteamID a1, unsigned int a2, unsigned short a3, CSteamID a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking005::AddRequestLobbyListFilter(const char *a1, const char *a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking005::AddRequestLobbyListNumericalFilter(const char *a1, int a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking005::AddRequestLobbyListSlotsAvailableFilter()
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking005::GetLobbyGameServer(CSteamID a1, unsigned int *a2, unsigned short *a3, CSteamID *a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

int CSteamMatchMaking005::GetLobbyMemberLimit(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__);
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberLimit(a1);
}

void CSteamMatchMaking005::SetLobbyMemberLimit(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s (%u)\n", __FUNCTION__, a2); 
}

void CSteamMatchMaking005::RequestFriendsLobbies()
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking005::AddRequestLobbyListNearValueFilter(const char *a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

void CSteamMatchMaking005::GetLobbyDistance(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}

int CSteamMatchMaking005::GetLobbyOwner(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyOwner(a1);
}

void CSteamMatchMaking005::SetLobbyType(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}