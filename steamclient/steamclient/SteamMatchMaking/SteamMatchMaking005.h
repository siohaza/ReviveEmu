/*
`vtable for'CAdapterSteamMatchmaking005
_ZN27CAdapterSteamMatchmaking00520GetFavoriteGameCountEv
_ZN27CAdapterSteamMatchmaking00515GetFavoriteGameEiPjS0_PtS1_S0_S0_
_ZN27CAdapterSteamMatchmaking00515AddFavoriteGameEjjttjj
_ZN27CAdapterSteamMatchmaking00518RemoveFavoriteGameEjjttj
_ZN27CAdapterSteamMatchmaking00516RequestLobbyListEv
_ZN27CAdapterSteamMatchmaking00525AddRequestLobbyListFilterEPKcS1_
_ZN27CAdapterSteamMatchmaking00534AddRequestLobbyListNumericalFilterEPKcii
_ZN27CAdapterSteamMatchmaking00539AddRequestLobbyListSlotsAvailableFilterEv
_ZN27CAdapterSteamMatchmaking00534AddRequestLobbyListNearValueFilterEPKci
_ZN27CAdapterSteamMatchmaking00515GetLobbyByIndexEi
_ZN27CAdapterSteamMatchmaking00511CreateLobbyE10ELobbyType
_ZN27CAdapterSteamMatchmaking0059JoinLobbyE8CSteamID
_ZN27CAdapterSteamMatchmaking00510LeaveLobbyE8CSteamID
_ZN27CAdapterSteamMatchmaking00517InviteUserToLobbyE8CSteamIDS0_
_ZN27CAdapterSteamMatchmaking00518GetNumLobbyMembersE8CSteamID
_ZN27CAdapterSteamMatchmaking00521GetLobbyMemberByIndexE8CSteamIDi
_ZN27CAdapterSteamMatchmaking00512GetLobbyDataE8CSteamIDPKc
_ZN27CAdapterSteamMatchmaking00512SetLobbyDataE8CSteamIDPKcS2_
_ZN27CAdapterSteamMatchmaking00518GetLobbyMemberDataE8CSteamIDS0_PKc
_ZN27CAdapterSteamMatchmaking00518SetLobbyMemberDataE8CSteamIDPKcS2_
_ZN27CAdapterSteamMatchmaking00516SendLobbyChatMsgE8CSteamIDPKvi
_ZN27CAdapterSteamMatchmaking00517GetLobbyChatEntryE8CSteamIDiPS0_PviP14EChatEntryType
_ZN27CAdapterSteamMatchmaking00516RequestLobbyDataE8CSteamID
_ZN27CAdapterSteamMatchmaking00518SetLobbyGameServerE8CSteamIDjtS0_
_ZN27CAdapterSteamMatchmaking00518GetLobbyGameServerE8CSteamIDPjPtPS0_
_ZN27CAdapterSteamMatchmaking00519SetLobbyMemberLimitE8CSteamIDi
_ZN27CAdapterSteamMatchmaking00519GetLobbyMemberLimitE8CSteamID
_ZN27CAdapterSteamMatchmaking00521RequestFriendsLobbiesEv
_ZN27CAdapterSteamMatchmaking00512SetLobbyTypeE8CSteamID10ELobbyType
_ZN27CAdapterSteamMatchmaking00513GetLobbyOwnerE8CSteamID
_ZN27CAdapterSteamMatchmaking00516GetLobbyDistanceE8CSteamID

*/
#include ".\matchmakingtypes.h"
#include "..\Common\steamclientpublic.h"

class CSteamMatchMaking005
{
public:
	CSteamMatchMaking005();
	~CSteamMatchMaking005();

	virtual int GetFavoriteGameCount(void);
	virtual bool GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7);
	virtual int AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6);
	virtual bool RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4);
	virtual int RequestLobbyList();
	virtual void AddRequestLobbyListFilter(char  const* a1, char  const* a2);
	virtual void AddRequestLobbyListNumericalFilter(char  const* a1, int a2, int a3);
	virtual void AddRequestLobbyListSlotsAvailableFilter(void);
	virtual void AddRequestLobbyListNearValueFilter(char const* a1, int a2);
	virtual CSteamID GetLobbyByIndex(int a1);
	virtual void CreateLobby(int eLobbyType);
	virtual void JoinLobby(CSteamID a1);
	virtual void LeaveLobby(CSteamID a1);
	virtual bool InviteUserToLobby(CSteamID a1, CSteamID a2);
	virtual int GetNumLobbyMembers(CSteamID a1);
	virtual CSteamID GetLobbyMemberByIndex(CSteamID a1, int a2);
	virtual const char* GetLobbyData(CSteamID a1, char  const* a2);
	virtual void SetLobbyData(CSteamID a1, char  const* a2, char  const* a3);
	virtual const char* GetLobbyMemberData(CSteamID a1, CSteamID a2, char  const* a3);
	virtual void SetLobbyMemberData(CSteamID a1, char  const* a2, char  const* a3);
	virtual bool SendLobbyChatMsg(CSteamID a1, void  const* a2, int a3);
	virtual int GetLobbyChatEntry(CSteamID a1, int a2, CSteamID* a3, void * a4, int a5, EChatEntryType * a6);
    virtual void RequestLobbyData(CSteamID a1);
	virtual void SetLobbyGameServer(CSteamID a1, unsigned int a2, unsigned short a3, CSteamID a4);
	virtual void GetLobbyGameServer(CSteamID a1, unsigned int * a2, unsigned short * a3, CSteamID* a4);
	virtual void SetLobbyMemberLimit(CSteamID a1, int a2);
	virtual int GetLobbyMemberLimit(CSteamID a1);
	virtual void RequestFriendsLobbies(void);
	virtual void SetLobbyType(CSteamID a1, int a2);
	virtual int GetLobbyOwner(CSteamID a1);
	virtual void GetLobbyDistance(CSteamID a1);
};
