#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamFriends003.h"
#include ".\SteamFriends.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamFriends* g_pSteamFriends;

CSteamFriends003::CSteamFriends003()
{
}

CSteamFriends003::~CSteamFriends003()
{
}

const char* CSteamFriends003::GetPersonaName(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaName(); 
}
void CSteamFriends003::SetPersonaName(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetPersonaName(a1); 
}
EPersonaState CSteamFriends003::GetPersonaState(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaState(); 
}
int CSteamFriends003::GetFriendCount(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCount(a1);
}
CSteamID CSteamFriends003::GetFriendByIndex(int a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendByIndex(a1, a2);
}
EFriendRelationship CSteamFriends003::GetFriendRelationship(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendRelationship(a1);
}
EPersonaState CSteamFriends003::GetFriendPersonaState(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaState(a1);
}
const char* CSteamFriends003::GetFriendPersonaName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaName(a1);
}
int CSteamFriends003::GetFriendAvatar(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendAvatar(a1);
}
bool CSteamFriends003::GetFriendGamePlayed(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendGamePlayed(a1, a2, a3, a4);
}
const char* CSteamFriends003::GetFriendPersonaNameHistory(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaNameHistory(a1, a2);
}
bool CSteamFriends003::HasFriend(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->HasFriend(a1, a2);
}
int CSteamFriends003::GetClanCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanCount();
}
int CSteamFriends003::GetClanByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanByIndex(a1);
}
int CSteamFriends003::GetClanName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanName(a1);
}
int CSteamFriends003::GetFriendCountFromSource(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCountFromSource(a1);
}
int CSteamFriends003::GetFriendFromSourceByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendFromSourceByIndex(a1, a2);
}
int CSteamFriends003::IsUserInSource(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->IsUserInSource(a1, a2);
}
int CSteamFriends003::SetInGameVoiceSpeaking(CSteamID a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetInGameVoiceSpeaking(a1, a2);
}
void CSteamFriends003::ActivateGameOverlay(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->ActivateGameOverlay(a1);
}