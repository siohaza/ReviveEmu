#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamFriends002.h"
#include ".\SteamFriends.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamFriends* g_pSteamFriends;

CSteamFriends002::CSteamFriends002()
{
}

CSteamFriends002::~CSteamFriends002()
{
}

const char* CSteamFriends002::GetPersonaName(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaName(); 
}
void CSteamFriends002::SetPersonaName(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetPersonaName(a1); 
}
EPersonaState CSteamFriends002::GetPersonaState(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaState(); 
}
void CSteamFriends002::SetPersonaState(EPersonaState a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetPersonaState(a1); 
}
int CSteamFriends002::GetFriendCount(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCount(a1);
}
CSteamID CSteamFriends002::GetFriendByIndex(int a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendByIndex(a1, a2);
}
EFriendRelationship CSteamFriends002::GetFriendRelationship(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendRelationship(a1);
}
EPersonaState CSteamFriends002::GetFriendPersonaState(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaState(a1);
}
const char* CSteamFriends002::GetFriendPersonaName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaName(a1);
}
void CSteamFriends002::SetFriendRegValue(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetFriendRegValue(a1, a2, a3);
}
const char* CSteamFriends002::GetFriendRegValue(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendRegValue(a1, a2);
}
bool CSteamFriends002::GetFriendGamePlayed(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendGamePlayed(a1, a2, a3, a4);
}
const char* CSteamFriends002::GetFriendPersonaNameHistory(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaNameHistory(a1, a2);
}
bool CSteamFriends002::AddFriend(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->AddFriend(a1);
}
bool CSteamFriends002::RemoveFriend(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->RemoveFriend(a1);
}
bool CSteamFriends002::HasFriend(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->HasFriend(a1, a2);
}
int CSteamFriends002::AddFriendByName(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->AddFriendByName(a1);
}
int CSteamFriends002::InviteFriendByEmail(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->InviteFriendByEmail(a1);
}
int CSteamFriends002::GetChatMessage(CSteamID a1, int a2, void * a3, int a4, EChatEntryType * a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetChatMessage(a1, a2, a3, a4, a5);
}
bool CSteamFriends002::SendMsgToFriend(CSteamID a1, EChatEntryType a2, void  const* a3, int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SendMsgToFriend(a1, a2, a3, a4);
}
int CSteamFriends002::GetChatIDOfChatHistoryStart(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetChatIDOfChatHistoryStart(a1);
}
void CSteamFriends002::SetChatHistoryStart(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetChatHistoryStart(a1, a2);
}
void CSteamFriends002::ClearChatHistory(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->ClearChatHistory(a1);
}
int CSteamFriends002::GetClanCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanCount();
}
int CSteamFriends002::GetClanByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanByIndex(a1);
}
int CSteamFriends002::GetClanName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetClanName(a1);
}
int CSteamFriends002::InviteFriendToClan(CSteamID a1, CSteamID a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->InviteFriendToClan(a1, a2);
}
int CSteamFriends002::AcknowledgeInviteToClan(CSteamID a1, bool a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->AcknowledgeInviteToClan(a1, a2);
}
int CSteamFriends002::GetFriendCountFromSource(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCountFromSource(a1);
}
int CSteamFriends002::GetFriendFromSourceByIndex(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendFromSourceByIndex(a1, a2);
}
