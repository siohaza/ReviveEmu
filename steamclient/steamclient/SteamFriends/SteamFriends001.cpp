#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamFriends001.h"
#include ".\SteamFriends.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamFriends* g_pSteamFriends;

CSteamFriends001::CSteamFriends001()
{
}

CSteamFriends001::~CSteamFriends001()
{
}

const char* CSteamFriends001::GetPersonaName(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaName(); 
}
void CSteamFriends001::SetPersonaName(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetPersonaName(a1); 
}
EPersonaState CSteamFriends001::GetPersonaState(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetPersonaState(); 
}
void CSteamFriends001::SetPersonaState(EPersonaState a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetPersonaState(a1); 
}
bool CSteamFriends001::AddFriend(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->AddFriend(a1);
}
bool CSteamFriends001::RemoveFriend(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->RemoveFriend(a1);
}
bool CSteamFriends001::HasFriend(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->HasFriend(a1);
}
EFriendRelationship CSteamFriends001::GetFriendRelationship(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendRelationship(a1);
}
EPersonaState CSteamFriends001::GetFriendPersonaState(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaState(a1);
}
void CSteamFriends001::Deprecated_GetFriendGamePlayed(CSteamID a1, int * a2, unsigned int * a3, unsigned short * a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	//g_pSteamFriends = GSteamFriends();
	//return g_pSteamFriends->GetPersonaName();
}
const char* CSteamFriends001::GetFriendPersonaName(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaName(a1);
}
int CSteamFriends001::AddFriendByName(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->AddFriendByName(a1);
}
int CSteamFriends001::GetFriendCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendCount();
}
CSteamID CSteamFriends001::GetFriendByIndex(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendByIndex(a1);
}
int CSteamFriends001::SendMsgToFriend(CSteamID a1, EChatEntryType a2, char  const* a3, int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SendMsgToFriend(a1, a2, a3, a4);
}
void CSteamFriends001::SetFriendRegValue(CSteamID a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetFriendRegValue(a1, a2, a3);
}
const char* CSteamFriends001::GetFriendRegValue(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendRegValue(a1, a2);
}
const char* CSteamFriends001::GetFriendPersonaNameHistory(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendPersonaNameHistory(a1, a2);
}
int CSteamFriends001::GetChatMessage(CSteamID a1, int a2, void * a3, int a4, EChatEntryType * a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetChatMessage(a1, a2, a3, a4, a5);
}
bool CSteamFriends001::SendMsgToFriend(CSteamID a1, EChatEntryType a2, void  const* a3, int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SendMsgToFriend(a1, a2, a3, a4);
}
int CSteamFriends001::GetChatIDOfChatHistoryStart(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetChatIDOfChatHistoryStart(a1);
}
void CSteamFriends001::SetChatHistoryStart(CSteamID a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->SetChatHistoryStart(a1, a2);
}
void CSteamFriends001::ClearChatHistory(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->ClearChatHistory(a1);
}
int CSteamFriends001::InviteFriendByEmail(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->InviteFriendByEmail(a1);
}
void CSteamFriends001::GetBlockedFriendCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	//g_pSteamFriends = GSteamFriends();
	//return g_pSteamFriends->GetBlockedFriendCount();
}
bool CSteamFriends001::GetFriendGamePlayed(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendGamePlayed(a1, a2, a3, a4);
}
bool CSteamFriends001::GetFriendGamePlayed2(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamFriends = GSteamFriends();
	return g_pSteamFriends->GetFriendGamePlayed(a1, a2, a3, a4);
}