#include ".\SteamMatchMaking.h"
#include ".\SteamMatchMakingServers\SteamMatchMakingServers.h"
#include <vector>

extern CSteamMatchMakingServers* g_pSteamMatchMakingServers;
extern std::vector<CallbackMsg_t*> g_CallbackMsgList;

 CSteamMatchMaking* g_pSteamMatchMaking;

 CSteamMatchMaking* GSteamMatchMaking()
 {
	 static CSteamMatchMaking g_SteamMatchMaking;
	 return &g_SteamMatchMaking;
 }

 CSteamMatchMaking::CSteamMatchMaking()
 {
 }

 CSteamMatchMaking::~CSteamMatchMaking()
 {
 }

int CSteamMatchMaking::GetFavoriteGameCount()
{ 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->GetServerCount(eFavoritesServer);
}

bool CSteamMatchMaking::GetFavoriteGame( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer )
{ 
	return 0; 
}
int CSteamMatchMaking::AddFavoriteGame( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer )
{ 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	return g_pSteamMatchMakingServers->AddToFavorites(nAppID, nIP, nConnPort, rTime32LastPlayedOnServer); 
}

bool CSteamMatchMaking::RemoveFavoriteGame( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 unFlags )
{ 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	if (g_pSteamMatchMakingServers)
	{
		return g_pSteamMatchMakingServers->RemoveFromFavorites(nAppID, nIP, nConnPort);
	}
	return 0; 
}

bool CSteamMatchMaking::GetFavoriteGame( int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer )
{ 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	if (g_pSteamMatchMakingServers)
	{
		return g_pSteamMatchMakingServers->GetFavoriteGame(iGame, pnAppID, pnIP, pnConnPort, pnQueryPort, punFlags, pRTime32LastPlayedOnServer);
	}
	return 1; 
}
int CSteamMatchMaking::AddFavoriteGame( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer ) 
{ 
		g_pSteamMatchMakingServers = GSteamMatchMakingServers();
		if (g_pSteamMatchMakingServers)
		{
			return g_pSteamMatchMakingServers->AddToFavorites(nAppID, nIP, nConnPort, rTime32LastPlayedOnServer);
		}
	return 0; 
}
bool CSteamMatchMaking::RemoveFavoriteGame( uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags )
{ 
	g_pSteamMatchMakingServers = GSteamMatchMakingServers();
	if (g_pSteamMatchMakingServers)
	{
		return g_pSteamMatchMakingServers->RemoveFromFavorites(nAppID, nIP, nConnPort);
	}
	return 0; 
}

void CSteamMatchMaking::RequestLobbyList( uint64 ulGameID, MatchMakingKeyValuePair_t *pFilters, uint32 nFilters ) 
{
}

int CSteamMatchMaking::RequestLobbyList()
{
	return 1;
}

CSteamID CSteamMatchMaking::GetLobbyByIndex( int iLobby ) 
{ 
	CSteamID a;
	return a;
}

void CSteamMatchMaking::CreateLobby( uint64 ulGameID, bool bPrivate )
{
}

void CSteamMatchMaking::CreateLobby( int eLobbyType )
{
	LobbyCreate_t* lobby = new LobbyCreate_t;
	lobby->m_eResult = k_EResultOK;
	lobby->m_ulSteamIDLobby = 1;

	CallbackMsg_t* callbackmsg = new CallbackMsg_t;
	callbackmsg->m_hSteamUser = 1;
	callbackmsg->m_iCallback = lobby->k_iCallback;
	callbackmsg->m_pubParam = (uint8*)lobby;
	callbackmsg->m_cubParam = sizeof(LobbyCreate_t);
	g_CallbackMsgList.push_back(callbackmsg);

	LobbyEnter_t* lobby2 = new LobbyEnter_t;
	lobby2->m_bLocked = false;
	lobby2->m_EChatRoomEnterResponse = 1;
	lobby2->m_rgfChatPermissions = 0xFFFFFFFF;
	lobby2->m_ulSteamIDLobby = 1;

	CallbackMsg_t* callbackmsg2 = new CallbackMsg_t;
	callbackmsg2->m_hSteamUser = 1;
	callbackmsg2->m_iCallback = lobby2->k_iCallback;
	callbackmsg2->m_pubParam = (uint8*)lobby2;
	callbackmsg2->m_cubParam = sizeof(LobbyEnter_t);
	g_CallbackMsgList.push_back(callbackmsg2);

}
// Join a lobby
void CSteamMatchMaking::JoinLobby( CSteamID steamIDLobby )
{
}
// Leave a lobby
void CSteamMatchMaking::LeaveLobby( CSteamID steamIDLobby )
{
}
// Invite someone to the lobby
bool CSteamMatchMaking::InviteUserToLobby( CSteamID steamIDLobby, CSteamID steamIDInvitee )
{ 
	return 0; 
}
// List users in this lobby
int CSteamMatchMaking::GetNumLobbyMembers( CSteamID steamIDLobby )
{ 
	return 4; 
}
CSteamID CSteamMatchMaking::GetLobbyMemberByIndex( CSteamID steamIDLobby, int iMember )
{ 
	__asm xor eax, eax 
}
// Get data associated with this lobby
const char* CSteamMatchMaking::GetLobbyData( CSteamID SteamIDLobby, const char *pchKey )
{ 
	return 0; 
}
// Update lobby data (Admin only)
void CSteamMatchMaking::SetLobbyData( CSteamID steamIDLobby, const char *pchKey, const char *pchValue )
{
}
// Get per-user data for someone in this lobby
const char* CSteamMatchMaking::GetLobbyMemberData( CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey )
{ 
	return 0;
}
// Update user data (for you only)
void CSteamMatchMaking::SetLobbyMemberData( CSteamID steamIDLobby, const char *pchKey, const char *pchValue )
{
}
// change the lobby Admin (Admin only)
void CSteamMatchMaking::ChangeLobbyAdmin( CSteamID steamIDLobby, CSteamID steamIDNewAdmin )
{
}
// Send a chat message to the lobby
bool CSteamMatchMaking::SendLobbyChatMsg( CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody )
{

	LobbyChatMsg_t* lobby = new LobbyChatMsg_t;
	lobby->m_eChatEntryType = 1;
	lobby->m_iChatID = 1;
	lobby->m_ulSteamIDLobby = 1;
	lobby->m_ulSteamIDUser = 1;

	CallbackMsg_t* callback = new CallbackMsg_t;
	callback->m_iCallback = lobby->k_iCallback;
	callback->m_hSteamUser = 1;
	callback->m_pubParam = (uint8*)lobby;
	callback->m_cubParam = sizeof(LobbyChatMsg_t);
	g_CallbackMsgList.push_back(callback);

	m_pvLobbyChatMsg = malloc(cubMsgBody);
	memset(m_pvLobbyChatMsg, 0, cubMsgBody);
	memcpy(m_pvLobbyChatMsg, pvMsgBody, cubMsgBody);

	return 1;
}
// Get a chat message entry
int CSteamMatchMaking::GetLobbyChatEntry( CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType )
{ 
	pSteamIDUser->Set(1, k_EUniversePublic, k_EAccountTypeChat);
	*peChatEntryType = k_EChatEntryTypeChatMsg;
	memcpy(pvData, m_pvLobbyChatMsg, cubData);
	return 1; 
}

void CSteamMatchMaking::RequestLobbyData(CSteamID a1)
{
}

void CSteamMatchMaking::SetLobbyGameServer(CSteamID a1, unsigned int a2, unsigned short a3, CSteamID a4)
{
}

int CSteamMatchMaking::GetLobbyOwner(CSteamID a1)
{
	return 1;
}

int CSteamMatchMaking::GetLobbyMemberLimit(CSteamID a1)
{
	return 8;
}