#include "..\Common\commonincludes.h"
#include ".\SteamFriends.h"

CSteamFriends* g_pSteamFriends;

extern char g_chName[50];

CSteamFriends::CSteamFriends()
{
}

CSteamFriends::~CSteamFriends()
{
}

const char* CSteamFriends::GetPersonaName()
{ 
	return g_chName; 
}
// sets the player name, stores it on the server and publishes the changes to all friends who are online
void CSteamFriends::SetPersonaName(const char* pchPersonaName)
{ 
	strcpy((char*)pchPersonaName, g_chName); 
}
// gets the friend status of the current user
EPersonaState CSteamFriends::GetPersonaState()
{ 
	return k_EPersonaStateOffline; 
}
// sets the status, communicates to server, tells all friends
void CSteamFriends::SetPersonaState(EPersonaState ePersonaState)
{
}

// friend iteration
int CSteamFriends::GetFriendCount(int a1)
{ 
	return 0; 
}
CSteamID CSteamFriends::GetFriendByIndex(int a1, int a2)
{ 
	CSteamID retval;
	static int iCount = 10;
	retval.Set(iCount, k_EUniversePublic, k_EAccountTypeIndividual);
	iCount++;
	return retval; 
} // CSteamID

// gets the relationship to a user
EFriendRelationship CSteamFriends::GetFriendRelationship(CSteamID steamIDFriend)
{ 
	return k_EFriendRelationshipFriend; 
}
// returns true if the specified user is considered a friend (can see our online status)
EPersonaState CSteamFriends::GetFriendPersonaState(CSteamID steamIDFriend)
{ 
	return k_EPersonaStateOffline;
}
// returns the name of a friend - guaranteed to not be NULL.
const char* CSteamFriends::GetFriendPersonaName(CSteamID a1)
{ 
	return g_chName;
}
int CSteamFriends::GetFriendAvatar(CSteamID steamIDFriend)
{ 
	return 1; 
}
int CSteamFriends::GetFriendAvatar(CSteamID steamIDFriend, int a2)
{ 
	return 1; 
}
// steam registry, accessed by friend
void CSteamFriends::SetFriendRegValue(CSteamID steamIDFriend, const char *pchKey, const char *pchValue)
{
}
const char* CSteamFriends::GetFriendRegValue(CSteamID steamIDFriend, const char* pchKey)
{ 
	return g_chName; 
}
// accesses old friends names - returns an empty string when their are no more items in the history
const char* CSteamFriends::GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName)
{ 
	return g_chName; 
}
// adds a friend to the users list.  Friend will be notified that they have been added, and have the option of accept/decline
bool CSteamFriends::AddFriend(CSteamID steamIDFriend)
{ 
	return true; 
}
// removes the friend from the list, and blocks them from contacting the user again
bool CSteamFriends::RemoveFriend(CSteamID steamIDFriend)
{ 
	return true;
}
// returns true if the specified user is considered a friend (can see our online status)
bool CSteamFriends::HasFriend(CSteamID a1, int a2)
{ 
	return false;
}
bool CSteamFriends::HasFriend(CSteamID a1)
{ 
	return false;
}
// adds a friend by email address or account name - value returned in callback
int CSteamFriends::AddFriendByName(const char *pchEmailOrAccountName)
{ 
	return 0; 
}
int CSteamFriends::InviteFriendByEmail(const char* a1)
{ 
	return 0; 
}

// chat message iteration
// returns the number of bytes in the message, filling pvData with as many of those bytes as possible
// returns 0 if the steamID or iChatID are invalid
int CSteamFriends::GetChatMessage(CSteamID steamIDFriend, int iChatID, void *pvData, int cubData, EChatEntryType *peFriendMsgType)
{ 
	return 0; 
}
// generic friend->friend message sending, takes a sized buffer
bool CSteamFriends::SendMsgToFriend(CSteamID a1, EChatEntryType a2, void  const* a3, int a4)
{ 
	return true; 
}
// returns the chatID that a chat should be resumed from when switching chat contexts
int CSteamFriends::GetChatIDOfChatHistoryStart(CSteamID steamIDFriend) 
{ 
	return 0; 
}
// sets where a chat with a user should resume
void CSteamFriends::SetChatHistoryStart(CSteamID steamIDFriend, int iChatID)
{
}
// clears the chat history - should be called when a chat dialog closes
// the chat history can still be recovered by another context using SetChatHistoryStart() to reset the ChatIDOfChatHistoryStart
void CSteamFriends::ClearChatHistory(CSteamID steamIDFriend)
{
}

int CSteamFriends::GetClanCount(){ return 0; }
int CSteamFriends::GetClanByIndex(int a1){ return 0; }
int CSteamFriends::GetClanName(CSteamID a1){ return 0; }
int CSteamFriends::InviteFriendToClan(CSteamID a1, CSteamID a2){ return 0; }
int CSteamFriends::AcknowledgeInviteToClan(CSteamID a1, bool a2){ return 0; }
int CSteamFriends::GetFriendCountFromSource(CSteamID a1){ return 0; }
int CSteamFriends::GetFriendFromSourceByIndex(CSteamID a1, int a2){ return 0; }
int CSteamFriends::IsUserInSource(CSteamID a1, CSteamID a2){ return 0; }
int CSteamFriends::SetInGameVoiceSpeaking(CSteamID a1, bool a2){ return 0; }
int CSteamFriends::SendMsgToFriend(CSteamID a1, EChatEntryType a2, char  const* a3, int a4) { return 0; }
void CSteamFriends::GetBlockedFriendCount() {  }
bool CSteamFriends::GetFriendGamePlayed(CSteamID a1, unsigned __int64 *a2, unsigned int *a3, unsigned short *a4, unsigned short *a5) { return false; }
bool CSteamFriends::GetFriendGamePlayed(CSteamID a1, FriendGameInfo_t* a2) 
{ 
	return false; 
}
bool CSteamFriends::GetFriendGamePlayed(CSteamID a1, int a2, int a3) 
{ 
	return false; 
}


void CSteamFriends::ActivateGameOverlay(const char* a1)
{ 
}

CSteamFriends* GSteamFriends(void)
{
	static CSteamFriends g_SteamFriends;
	return &g_SteamFriends;
}
