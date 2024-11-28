/*
`vtable for'CAdapterSteamFriends005
_ZN23CAdapterSteamFriends00514GetPersonaNameEv ; CAdapterSteamFriends005::GetPersonaName(void)
_ZN23CAdapterSteamFriends00514SetPersonaNameEPKc
_ZN23CAdapterSteamFriends00515GetPersonaStateEv
_ZN23CAdapterSteamFriends00514GetFriendCountEi
_ZN23CAdapterSteamFriends00516GetFriendByIndexEii
_ZN23CAdapterSteamFriends00521GetFriendRelationshipE8CSteamID
_ZN23CAdapterSteamFriends00521GetFriendPersonaStateE8CSteamID
_ZN23CAdapterSteamFriends00520GetFriendPersonaNameE8CSteamID
_ZN23CAdapterSteamFriends00515GetFriendAvatarE8CSteamIDi
_ZN23CAdapterSteamFriends00519GetFriendGamePlayedE8CSteamIDP16FriendGameInfo_t
_ZN23CAdapterSteamFriends00527GetFriendPersonaNameHistoryE8CSteamIDi
_ZN23CAdapterSteamFriends0059HasFriendE8CSteamIDi
_ZN23CAdapterSteamFriends00512GetClanCountEv
_ZN23CAdapterSteamFriends00514GetClanByIndexEi
_ZN23CAdapterSteamFriends00511GetClanNameE8CSteamID
_ZN23CAdapterSteamFriends00524GetFriendCountFromSourceE8CSteamID
_ZN23CAdapterSteamFriends00526GetFriendFromSourceByIndexE8CSteamIDi
_ZN23CAdapterSteamFriends00514IsUserInSourceE8CSteamIDS0_
_ZN23CAdapterSteamFriends00522SetInGameVoiceSpeakingE8CSteamIDb
_ZN23CAdapterSteamFriends00519ActivateGameOverlayEPKc
*/

#include ".\SteamFriends.h"

class CSteamFriends005
{
public:
	CSteamFriends005();
	~CSteamFriends005();

	virtual const char* GetPersonaName(void);
	virtual void SetPersonaName(char  const* a1);
	virtual EPersonaState GetPersonaState(void);
	virtual int GetFriendCount(int a1);
	virtual CSteamID GetFriendByIndex(int a1, int a2);
	virtual EFriendRelationship GetFriendRelationship(CSteamID a1);
	virtual EPersonaState GetFriendPersonaState(CSteamID a1);
	virtual const char* GetFriendPersonaName(CSteamID a1);
	virtual int GetFriendAvatar(CSteamID a1, int a2);
	virtual bool GetFriendGamePlayed(CSteamID a1, int a2, int a3);
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