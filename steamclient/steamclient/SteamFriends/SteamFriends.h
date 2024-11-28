#pragma once

#include "..\Common\steamclientpublic.h"

struct FriendGameInfo_t
{
	unsigned int m1;
	unsigned int m2;
};

//-----------------------------------------------------------------------------
// Purpose: set of relationships to other users
//-----------------------------------------------------------------------------
enum EFriendRelationship
{
	k_EFriendRelationshipNone = 0,
	k_EFriendRelationshipBlocked = 1,
	k_EFriendRelationshipRequestingFriendship = 2,
	k_EFriendRelationshipFriend = 3,
};


//-----------------------------------------------------------------------------
// Purpose: list of states a friend can be in
//-----------------------------------------------------------------------------
enum EPersonaState
{
	k_EPersonaStateOffline = 0,			// friend is not currently logged on
	k_EPersonaStateOnline = 1,			// friend is logged on
	k_EPersonaStateBusy = 2,			// user is on, but busy
	k_EPersonaStateAway = 3,			// auto-away feature
	k_EPersonaStateSnooze = 4,			// auto-away for a long time
	k_EPersonaStateMax,
};


//-----------------------------------------------------------------------------
// Purpose: friend-to-friend message types
//-----------------------------------------------------------------------------
enum EFriendMsgType
{
	k_EFriendMsgTypeChat = 1,			// chat test message
	k_EFriendMsgTypeTyping = 2,			// lets the friend know the other user has starting typing a chat message
	k_EFriendMsgTypeInvite = 3,			// invites the friend into the users current game
	k_EFriendMsgTypeChatSent = 4,		// chat that the user has sent to a friend
};

enum { k_cchPersonaNameMax = 128 };


class CSteamFriends
{
public:
	CSteamFriends();
	~CSteamFriends();

	virtual const char* GetPersonaName(void);
	virtual void SetPersonaName(char  const* a1);
	virtual EPersonaState GetPersonaState(void);
	virtual void SetPersonaState(EPersonaState a1);
	virtual bool AddFriend(CSteamID a1);
	virtual bool RemoveFriend(CSteamID a1);
	virtual bool HasFriend(CSteamID a1);
	virtual bool HasFriend(CSteamID a1, int a2);
	virtual EFriendRelationship GetFriendRelationship(CSteamID a1);
	virtual EPersonaState GetFriendPersonaState(CSteamID a1);
	virtual const char* GetFriendPersonaName(CSteamID a1);
	virtual int AddFriendByName(char  const* a1);
	virtual int GetFriendCount(int a1 = 0);
	virtual CSteamID GetFriendByIndex(int a1, int a2 = 0);
	virtual int SendMsgToFriend(CSteamID a1, EChatEntryType a2, char  const* a3, int a4);
	virtual void SetFriendRegValue(CSteamID a1, char  const* a2, char  const* a3);
	virtual const char* GetFriendRegValue(CSteamID a1, char  const* a2);
	virtual const char* GetFriendPersonaNameHistory(CSteamID a1, int a2);
	virtual int GetChatMessage(CSteamID a1, int a2, void * a3, int a4, EChatEntryType * a5);
	virtual bool SendMsgToFriend(CSteamID a1, EChatEntryType a2, void  const* a3, int a4);
	virtual int GetChatIDOfChatHistoryStart(CSteamID a1);
	virtual void SetChatHistoryStart(CSteamID a1, int a2);
	virtual void ClearChatHistory(CSteamID a1);
	virtual int InviteFriendByEmail(char  const* a1);
	virtual void GetBlockedFriendCount(void);
	virtual bool GetFriendGamePlayed(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5 = 0);
	virtual bool GetFriendGamePlayed(CSteamID a1, FriendGameInfo_t* a2);
	virtual bool GetFriendGamePlayed(CSteamID a1, int a2, int a3);
	virtual int GetFriendAvatar(CSteamID a1);
	virtual int GetFriendAvatar(CSteamID a1, int a2);
	virtual int GetClanCount(void);
	virtual int GetClanByIndex(int a1);
	virtual int GetClanName(CSteamID a1);
	virtual int GetFriendCountFromSource(CSteamID a1);
	virtual int GetFriendFromSourceByIndex(CSteamID a1, int a2);
	virtual int IsUserInSource(CSteamID a1, CSteamID a2);
	virtual int SetInGameVoiceSpeaking(CSteamID a1, bool a2);
	virtual void ActivateGameOverlay(char  const* a1);
	virtual int InviteFriendToClan(CSteamID a1, CSteamID a2);
	virtual int AcknowledgeInviteToClan(CSteamID a1, bool a2);
};

CSteamFriends* GSteamFriends(void);