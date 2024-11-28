#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamFriends005.h"
#include ".\SteamFriends.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamFriends* g_pSteamFriends;

CSteamFriends005::CSteamFriends005()
{
}

CSteamFriends005::~CSteamFriends005()
{
}

const char* CSteamFriends005::GetPersonaName(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaName(); 
}
void CSteamFriends005::SetPersonaName(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetPersonaName(a1); 
}
EPersonaState CSteamFriends005::GetPersonaState(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaState(); 
}
int CSteamFriends005::GetFriendCount(int a1)
{
	if (g_bLogging) Logger->Write("%s (%u)\n", __FUNCTION__, a1); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCount(a1);
}
CSteamID CSteamFriends005::GetFriendByIndex(int a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendByIndex(a1, a2);
}
EFriendRelationship CSteamFriends005::GetFriendRelationship(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendRelationship(a1);
}
EPersonaState CSteamFriends005::GetFriendPersonaState(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaState(a1);
}
const char* CSteamFriends005::GetFriendPersonaName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaName(a1);
}
int CSteamFriends005::GetFriendAvatar(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendAvatar(a1, a2);
}
bool CSteamFriends005::GetFriendGamePlayed(CSteamID a1, int a2, int a3)

{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendGamePlayed(a1, a2, a3);
}
const char* CSteamFriends005::GetFriendPersonaNameHistory(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaNameHistory(a1, a2);
}
bool CSteamFriends005::HasFriend(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->HasFriend(a1, a2);
}
int CSteamFriends005::GetClanCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanCount();
}
int CSteamFriends005::GetClanByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanByIndex(a1);
}
int CSteamFriends005::GetClanName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanName(a1);
}
int CSteamFriends005::GetFriendCountFromSource(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCountFromSource(a1);
}
int CSteamFriends005::GetFriendFromSourceByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendFromSourceByIndex(a1, a2);
}
int CSteamFriends005::IsUserInSource(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->IsUserInSource(a1, a2);
}
int CSteamFriends005::SetInGameVoiceSpeaking(CSteamID a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetInGameVoiceSpeaking(a1, a2);
}
void CSteamFriends005::ActivateGameOverlay(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->ActivateGameOverlay(a1);
}