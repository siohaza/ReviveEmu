#include ".\SteamFriends.h"

class CSteamFriends002
{
public:
	CSteamFriends002();
	~CSteamFriends002();

	virtual const char* GetPersonaName(void);
	virtual void SetPersonaName(char  const* a1);
	virtual EPersonaState GetPersonaState(void);
	virtual void SetPersonaState(EPersonaState a1);
	virtual int GetFriendCount(int a1);
	virtual CSteamID GetFriendByIndex(int a1, int a2);
	virtual EFriendRelationship GetFriendRelationship(CSteamID a1);
	virtual EPersonaState GetFriendPersonaState(CSteamID a1);
	virtual const char* GetFriendPersonaName(CSteamID a1);
	virtual void SetFriendRegValue(CSteamID a1, char  const* a2, char  const* a3);
	virtual const char* GetFriendRegValue(CSteamID a1, char  const* a2);
	virtual bool GetFriendGamePlayed(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5);
	virtual const char* GetFriendPersonaNameHistory(CSteamID a1, int a2);
	virtual bool AddFriend(CSteamID a1);
	virtual bool RemoveFriend(CSteamID a1);
	virtual bool HasFriend(CSteamID a1, int a2);
	virtual int AddFriendByName(char  const* a1);
	virtual int InviteFriendByEmail(char  const* a1);
	virtual int GetChatMessage(CSteamID a1, int a2, void * a3, int a4, EChatEntryType * a5);
	virtual bool SendMsgToFriend(CSteamID a1, EChatEntryType a2, void  const* a3, int a4);
	virtual int GetChatIDOfChatHistoryStart(CSteamID a1);
	virtual void SetChatHistoryStart(CSteamID a1, int a2);
	virtual void ClearChatHistory(CSteamID a1);
	virtual int GetClanCount(void);
	virtual int GetClanByIndex(int a1);
	virtual int GetClanName(CSteamID a1);
	virtual int InviteFriendToClan(CSteamID a1, CSteamID a2);
	virtual int AcknowledgeInviteToClan(CSteamID a1, bool a2);
	virtual int GetFriendCountFromSource(CSteamID a1);
	virtual int GetFriendFromSourceByIndex(CSteamID a1, int a2);
};