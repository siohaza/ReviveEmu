#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamFriends004.h"
#include ".\SteamFriends.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamFriends* g_pSteamFriends;

CSteamFriends004::CSteamFriends004()
{
}

CSteamFriends004::~CSteamFriends004()
{
}

const char* CSteamFriends004::GetPersonaName(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaName(); 
}
void CSteamFriends004::SetPersonaName(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetPersonaName(a1); 
}
EPersonaState CSteamFriends004::GetPersonaState(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaState(); 
}
int CSteamFriends004::GetFriendCount(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCount(a1);
}
CSteamID CSteamFriends004::GetFriendByIndex(int a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendByIndex(a1, a2);
}
EFriendRelationship CSteamFriends004::GetFriendRelationship(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendRelationship(a1);
}
EPersonaState CSteamFriends004::GetFriendPersonaState(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaState(a1);
}
const char* CSteamFriends004::GetFriendPersonaName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaName(a1);
}
int CSteamFriends004::GetFriendAvatar(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendAvatar(a1, a2);
}
bool CSteamFriends004::GetFriendGamePlayed(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendGamePlayed(a1, a2, a3, a4);
}
const char* CSteamFriends004::GetFriendPersonaNameHistory(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaNameHistory(a1, a2);
}
bool CSteamFriends004::HasFriend(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->HasFriend(a1, a2);
}
int CSteamFriends004::GetClanCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanCount();
}
int CSteamFriends004::GetClanByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanByIndex(a1);
}
int CSteamFriends004::GetClanName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanName(a1);
}
int CSteamFriends004::GetFriendCountFromSource(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCountFromSource(a1);
}
int CSteamFriends004::GetFriendFromSourceByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendFromSourceByIndex(a1, a2);
}
int CSteamFriends004::IsUserInSource(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->IsUserInSource(a1, a2);
}
int CSteamFriends004::SetInGameVoiceSpeaking(CSteamID a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetInGameVoiceSpeaking(a1, a2);
}
void CSteamFriends004::ActivateGameOverlay(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->ActivateGameOverlay(a1);
}