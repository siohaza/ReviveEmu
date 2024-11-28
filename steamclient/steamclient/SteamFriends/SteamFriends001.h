#include "..\Common\steamclientpublic.h"
#include ".\SteamFriends.h"

class CSteamFriends001
{
public:
	CSteamFriends001();
	~CSteamFriends001();

	virtual const char* GetPersonaName(void);
	virtual void SetPersonaName(char  const* a1);
	virtual EPersonaState GetPersonaState(void);
	virtual void SetPersonaState(EPersonaState a1);
	virtual bool AddFriend(CSteamID a1);
	virtual bool RemoveFriend(CSteamID a1);
	virtual bool HasFriend(CSteamID a1);
	virtual EFriendRelationship GetFriendRelationship(CSteamID a1);
	virtual EPersonaState GetFriendPersonaState(CSteamID a1);
	virtual void Deprecated_GetFriendGamePlayed(CSteamID a1, int * a2, unsigned int * a3, unsigned short * a4);
	virtual const char* GetFriendPersonaName(CSteamID a1);
	virtual int AddFriendByName(char  const* a1);
	virtual int GetFriendCount(void);
	virtual CSteamID GetFriendByIndex(int a1);
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
	virtual bool GetFriendGamePlayed(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4);
	virtual bool GetFriendGamePlayed2(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5);
};
