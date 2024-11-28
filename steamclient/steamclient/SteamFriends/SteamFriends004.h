#include ".\SteamFriends.h"

class CSteamFriends004
{
public:
	CSteamFriends004();
	~CSteamFriends004();

	virtual const char* GetPersonaName(void);
	virtual void SetPersonaName(char  const* a1);
	virtual EPersonaState GetPersonaState(void);
	virtual int GetFriendCount(int a1);
	virtual CSteamID GetFriendByIndex(int a1, int a2);
	virtual EFriendRelationship GetFriendRelationship(CSteamID a1);
	virtual EPersonaState GetFriendPersonaState(CSteamID a1);
	virtual const char* GetFriendPersonaName(CSteamID a1);
	virtual int GetFriendAvatar(CSteamID a1, int a2);
	virtual bool GetFriendGamePlayed(CSteamID a1, unsigned long long * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5);
	virtual const char* GetFriendPersonaNameHistory(CSteamID a1, int a2);
	virtual bool HasFriend(CSteamID a1, int a2);
	virtual int GetClanCount(void);
	virtual int GetClanByIndex(int a1);
	virtual int GetClanName(CSteamID a1);
	virtual int GetFriendCountFromSource(CSteamID a1);
	virtual int GetFriendFromSourceByIndex(CSteamID a1, int a2);
	virtual int IsUserInSource(CSteamID a1, CSteamID a2);
	virtual int SetInGameVoiceSpeaking(CSteamID a1, bool a2);
	virtual void ActivateGameOverlay(char  const* a1);
};