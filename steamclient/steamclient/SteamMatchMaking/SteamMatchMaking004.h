/*
`vtable for'CAdapterSteamMatchmaking004
_ZN27CAdapterSteamMatchmaking00420GetFavoriteGameCountEv
_ZN27CAdapterSteamMatchmaking00415GetFavoriteGameEiPjS0_PtS1_S0_S0_
_ZN27CAdapterSteamMatchmaking00415AddFavoriteGameEjjttjj
_ZN27CAdapterSteamMatchmaking00418RemoveFavoriteGameEjjttj
_ZN27CAdapterSteamMatchmaking00416RequestLobbyListEv
_ZN27CAdapterSteamMatchmaking00425AddRequestLobbyListFilterEPKcS1_
_ZN27CAdapterSteamMatchmaking00434AddRequestLobbyListNumericalFilterEPKcii
_ZN27CAdapterSteamMatchmaking00439AddRequestLobbyListSlotsAvailableFilterEv
_ZN27CAdapterSteamMatchmaking00415GetLobbyByIndexEi
_ZN27CAdapterSteamMatchmaking00411CreateLobbyEb
_ZN27CAdapterSteamMatchmaking0049JoinLobbyE8CSteamID
_ZN27CAdapterSteamMatchmaking00410LeaveLobbyE8CSteamID
_ZN27CAdapterSteamMatchmaking00417InviteUserToLobbyE8CSteamIDS0_
_ZN27CAdapterSteamMatchmaking00418GetNumLobbyMembersE8CSteamID
_ZN27CAdapterSteamMatchmaking00421GetLobbyMemberByIndexE8CSteamIDi
_ZN27CAdapterSteamMatchmaking00412GetLobbyDataE8CSteamIDPKc
_ZN27CAdapterSteamMatchmaking00412SetLobbyDataE8CSteamIDPKcS2_
_ZN27CAdapterSteamMatchmaking00418GetLobbyMemberDataE8CSteamIDS0_PKc
_ZN27CAdapterSteamMatchmaking00418SetLobbyMemberDataE8CSteamIDPKcS2_
_ZN27CAdapterSteamMatchmaking00416SendLobbyChatMsgE8CSteamIDPKvi
_ZN27CAdapterSteamMatchmaking00417GetLobbyChatEntryE8CSteamIDiPS0_PviP14EChatEntryType
_ZN27CAdapterSteamMatchmaking00416RequestLobbyDataE8CSteamID
_ZN27CAdapterSteamMatchmaking00418SetLobbyGameServerE8CSteamIDjtS0_
_ZN27CAdapterSteamMatchmaking00418GetLobbyGameServerE8CSteamIDPjPtPS0_
_ZN27CAdapterSteamMatchmaking00419SetLobbyMemberLimitE8CSteamIDi
_ZN27CAdapterSteamMatchmaking00419GetLobbyMemberLimitE8CSteamID
_ZN27CAdapterSteamMatchmaking00421RequestFriendsLobbiesEv

*/

#include ".\matchmakingtypes.h"
#include "..\Common\steamclientpublic.h"

class CSteamMatchMaking004
{
public:
	CSteamMatchMaking004();
	~CSteamMatchMaking004();

	virtual int GetFavoriteGameCount(void);
	virtual bool GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7);
	virtual int AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6);
	virtual bool RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4);
	virtual void RequestLobbyList(unsigned long long a1, MatchMakingKeyValuePair_t * a2, unsigned int a3);
	virtual void AddRequestLobbyListFilter(char  const* a1, char  const* a2);
	virtual void AddRequestLobbyListNumericalFilter(char  const* a1, int a2, int a3);
	virtual void AddRequestLobbyListSlotsAvailableFilter(void);
	virtual CSteamID GetLobbyByIndex(int a1);
	virtual void CreateLobby(unsigned long long a1, bool a2);
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
	virtual void GetLobbyMemberLimit(CSteamID a1);
	virtual void RequestFriendsLobbies(void);
};