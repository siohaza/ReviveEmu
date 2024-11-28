#pragma once

#include ".\matchmakingtypes.h"
#include "..\Common\steamclientpublic.h"


// a server was added/removed from the favorites list, you should refresh now
struct FavoritesListChanged_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 2 }; // +2 as +1 was a previous version of this call with a different layout
	uint32 m_nIP; // an IP of 0 means reload the whole list, any other value means just one server
	uint32 m_nQueryPort;
	uint32 m_nConnPort;
	uint32 m_nAppID;
	uint32 m_nFlags;
	bool m_bAdd; // true if this is adding the entry, otherwise it is a remove
};

//-----------------------------------------------------------------------------
// Purpose: Someone has invited you to join a Lobby
//-----------------------------------------------------------------------------
struct LobbyInvite_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 3 };

	uint64 m_ulSteamIDUser;		// Steam ID of the person making the invite
	uint64 m_ulSteamIDLobby;	// Steam ID of the Lobby
};

//-----------------------------------------------------------------------------
// Purpose: You have entered a Lobby
//-----------------------------------------------------------------------------
struct LobbyEnter_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 4 };

	uint64 m_ulSteamIDLobby;							// SteamID of the Lobby you have entered
	uint32 m_rgfChatPermissions;						// Permissions of the current user
	bool m_bLocked;										// If true, then only invited users may join
	uint32 m_EChatRoomEnterResponse;	// EChatRoomEnterResponse
};

//-----------------------------------------------------------------------------
// Purpose: The lobby data has changed
//-----------------------------------------------------------------------------
struct LobbyDataUpdate_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 5 };

	uint64 m_ulSteamIDLobby;		// steamID of the Lobby
	uint64 m_ulSteamIDMember;		// steamID of the member whose data changed, or the room itself
};


//-----------------------------------------------------------------------------
// Purpose: The lobby chat room state has changed
//-----------------------------------------------------------------------------
struct LobbyChatUpdate_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 6 };

	uint64 m_ulSteamIDLobby;			// Lobby ID
	uint64 m_ulSteamIDUserChanged;		// user who's status in the lobby just changed - can be recipient
	uint64 m_ulSteamIDMakingChange;		// Chat member who made the change (different from SteamIDUserChange if kicking, muting, etc.)
	uint32 m_rgfChatMemberStateChange;	// bitfield of EChatMemberStateChange values
};

//-----------------------------------------------------------------------------
// Purpose: A chat message for this lobby
//-----------------------------------------------------------------------------
struct LobbyChatMsg_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 7 };

	uint64 m_ulSteamIDLobby;			// the lobby id this is in
	uint64 m_ulSteamIDUser;			// steamID of the user who has sent this message
	uint8 m_eChatEntryType;			// type of message
	uint32 m_iChatID;				// index of the chat entry to lookup
};

//-----------------------------------------------------------------------------
// Purpose: There's a change of Admin in this Lobby
//-----------------------------------------------------------------------------
struct LobbyAdminChange_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 8 };

	uint64 m_ulSteamIDLobby;
	uint64 m_ulSteamIDNewAdmin;
};


//-----------------------------------------------------------------------------
// Purpose: The Admin of a Lobby has created a game to join
//-----------------------------------------------------------------------------
struct LobbyGameCreated_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 9 };

	uint64 m_ulSteamIDLobby;
	uint32 m_unIP;
	uint16 m_usPort;
};

//-----------------------------------------------------------------------------
// Purpose: Number of matching lobbies found, iterate with GetLobbyByIndex
//-----------------------------------------------------------------------------
struct LobbyMatchList_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 10 };
	uint32 m_nLobbiesMatching;		// Number of lobbies that matched search criteria and we have SteamIDs for
};


//-----------------------------------------------------------------------------
// Purpose: The Lobby is closing
//-----------------------------------------------------------------------------
struct LobbyClosing_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 11 };
	uint64 m_ulSteamIDLobby;			// Lobby
};


//-----------------------------------------------------------------------------
// Purpose: You have been kicked from the lobby
//-----------------------------------------------------------------------------
struct LobbyKicked_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 12 };
	uint64 m_ulSteamIDLobby;			// Lobby
	uint64 m_ulSteamIDAdmin;			// User who kicked you
};


//-----------------------------------------------------------------------------
// Purpose: Result of our request to create a Lobby
//-----------------------------------------------------------------------------
struct LobbyCreate_t
{
	enum { k_iCallback = k_iSteamMatchmakingCallbacks + 13 };
	EResult m_eResult;				// Result
	uint64 m_ulSteamIDLobby;		// chat room, zero if failed
};

class CSteamMatchMaking
{
public:
	CSteamMatchMaking();
	~CSteamMatchMaking();

	virtual int GetFavoriteGameCount(void);
	virtual bool GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned int * a5, unsigned int * a6);
	virtual int AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4, unsigned int a5);
	virtual bool RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4);
	virtual bool GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7);
	virtual int AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6);
	virtual bool RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5);
	virtual void RequestLobbyList(unsigned long long a1, MatchMakingKeyValuePair_t * a2, unsigned int a3);
	virtual int RequestLobbyList();
	virtual CSteamID GetLobbyByIndex(int a1);
	virtual void CreateLobby(unsigned long long a1, bool a2);
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
	virtual void ChangeLobbyAdmin(CSteamID a1, CSteamID a2);
	virtual bool SendLobbyChatMsg(CSteamID a1, void  const* a2, int a3);
	virtual int GetLobbyChatEntry(CSteamID a1, int a2, CSteamID* a3, void * a4, int a5, EChatEntryType * a6);
    virtual void RequestLobbyData(CSteamID a1);
	virtual void SetLobbyGameServer(CSteamID a1, unsigned int a2, unsigned short a3, CSteamID a4);
	virtual int GetLobbyOwner(CSteamID a1);
	virtual int GetLobbyMemberLimit(CSteamID a1);

private:
	void* m_pvLobbyChatMsg;
};

 CSteamMatchMaking* GSteamMatchMaking();