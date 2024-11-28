#include "..\Common\commonincludes.h"
#include ".\SteamMatchMaking002.h"
#include ".\SteamMatchMaking.h"
#include ".\matchmakingtypes.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamMatchMaking* g_pSteamMatchMaking;

CSteamMatchMaking002::CSteamMatchMaking002()
{
}

CSteamMatchMaking002::~CSteamMatchMaking002()
{
}

int CSteamMatchMaking002::GetFavoriteGameCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGameCount(); 
}
bool CSteamMatchMaking002::GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGame(a1, a2, a3, a4, a5, a6, a7); 
}
int CSteamMatchMaking002::AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->AddFavoriteGame(a1, a2, a3, a4, a5, a6); 
}
bool CSteamMatchMaking002::RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RemoveFavoriteGame(a1, a2, a3, a4); 
}
void CSteamMatchMaking002::RequestLobbyList(unsigned long long a1, MatchMakingKeyValuePair_t * a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RequestLobbyList(a1, a2, a3); 
}
CSteamID CSteamMatchMaking002::GetLobbyByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyByIndex(a1); 
}
void CSteamMatchMaking002::CreateLobby(unsigned long long a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->CreateLobby(a1, a2); 
}
void CSteamMatchMaking002::JoinLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->JoinLobby(a1); 
}
void CSteamMatchMaking002::LeaveLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->LeaveLobby(a1); 
}
bool CSteamMatchMaking002::InviteUserToLobby(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->InviteUserToLobby(a1, a2); 
}
int CSteamMatchMaking002::GetNumLobbyMembers(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetNumLobbyMembers(a1); 
}
CSteamID CSteamMatchMaking002::GetLobbyMemberByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberByIndex(a1, a2); 
}
const char* CSteamMatchMaking002::GetLobbyData(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyData(a1, a2); 
}
void CSteamMatchMaking002::SetLobbyData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyData(a1, a2, a3); 
}
const char* CSteamMatchMaking002::GetLobbyMemberData(CSteamID a1, CSteamID a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberData(a1, a2, a3); 
}
void CSteamMatchMaking002::SetLobbyMemberData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyMemberData(a1, a2, a3); 
}
bool CSteamMatchMaking002::SendLobbyChatMsg(CSteamID a1, void  const* a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SendLobbyChatMsg(a1, a2, a3); 
}
int CSteamMatchMaking002::GetLobbyChatEntry(CSteamID a1, int a2, CSteamID* a3, void * a4, int a5, EChatEntryType * a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyChatEntry(a1, a2, a3, a4, a5, a6); 
}

void CSteamMatchMaking002::RequestLobbyData(CSteamID a1)
{
}

void CSteamMatchMaking002::SetLobbyGameServer(CSteamID a1, unsigned int a2, unsigned short a3, CSteamID a4)
{
}
