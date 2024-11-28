#include "..\Common\commonincludes.h"
#include ".\SteamMatchMaking001.h"
#include ".\SteamMatchMaking.h"
#include ".\matchmakingtypes.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamMatchMaking* g_pSteamMatchMaking;

CSteamMatchMaking001::CSteamMatchMaking001()
{
}

CSteamMatchMaking001::~CSteamMatchMaking001()
{
}

int CSteamMatchMaking001::GetFavoriteGameCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGameCount(); 
}
bool CSteamMatchMaking001::GetFavoriteGame2(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGame(a1, a2, a3, a4, a5, a6, a7); 
}
int CSteamMatchMaking001::AddFavoriteGame2(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->AddFavoriteGame(a1, a2, a3, a4, a5, a6); 
}
bool CSteamMatchMaking001::RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RemoveFavoriteGame(a1, a2, a3, a4); 
}
bool CSteamMatchMaking001::GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned int * a5, unsigned int * a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetFavoriteGame(a1, a2, a3, a4, a5, a6); 
}
int CSteamMatchMaking001::AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4, unsigned int a5)
{
	if (g_bLogging) Logger->Write("%s (%u, %u, %u, %u, %u)\n", __FUNCTION__, a1, a2, a3, a4, a5); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->AddFavoriteGame(a1, a2, a3, a4, a5); 
}
bool CSteamMatchMaking001::RemoveFavoriteGame2(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RemoveFavoriteGame(a1, a2, a3, a4, a5); 
}
void CSteamMatchMaking001::RequestLobbyList(unsigned long long a1, MatchMakingKeyValuePair_t * a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->RequestLobbyList(a1, a2, a3); 
}
CSteamID CSteamMatchMaking001::GetLobbyByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyByIndex(a1); 
}
void CSteamMatchMaking001::CreateLobby(unsigned long long a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->CreateLobby(a1, a2); 
}
void CSteamMatchMaking001::JoinLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->JoinLobby(a1); 
}
void CSteamMatchMaking001::LeaveLobby(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->LeaveLobby(a1); 
}
bool CSteamMatchMaking001::InviteUserToLobby(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->InviteUserToLobby(a1, a2); 
}
int CSteamMatchMaking001::GetNumLobbyMembers(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetNumLobbyMembers(a1); 
}
CSteamID CSteamMatchMaking001::GetLobbyMemberByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberByIndex(a1, a2); 
}
const char* CSteamMatchMaking001::GetLobbyData(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyData(a1, a2); 
}
void CSteamMatchMaking001::SetLobbyData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyData(a1, a2, a3); 
}
const char* CSteamMatchMaking001::GetLobbyMemberData(CSteamID a1, CSteamID a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyMemberData(a1, a2, a3); 
}
void CSteamMatchMaking001::SetLobbyMemberData(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SetLobbyMemberData(a1, a2, a3); 
}
void CSteamMatchMaking001::ChangeLobbyAdmin(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->ChangeLobbyAdmin(a1, a2); 
}
bool CSteamMatchMaking001::SendLobbyChatMsg(CSteamID a1, void  const* a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->SendLobbyChatMsg(a1, a2, a3); 
}
int CSteamMatchMaking001::GetLobbyChatEntry(CSteamID a1, int a2, CSteamID* a3, void * a4, int a5, EChatEntryType * a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamMatchMaking = GSteamMatchMaking();
	return g_pSteamMatchMaking->GetLobbyChatEntry(a1, a2, a3, a4, a5, a6); 
}
