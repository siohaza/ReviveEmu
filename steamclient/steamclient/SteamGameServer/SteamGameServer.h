#pragma once

// client has been approved to connect to this game server
struct GSClientApprove_t
{
	enum { k_iCallback = k_iSteamGameServerCallbacks + 1 };
	CSteamID m_SteamID;
};


// client has been denied to connection to this game server
struct GSClientDeny_t
{
	enum { k_iCallback = k_iSteamGameServerCallbacks + 2 };
	CSteamID m_SteamID;
	EDenyReason m_eDenyReason;
	char m_pchOptionalText[128];
};


// request the game server should kick the user
struct GSClientKick_t
{
	enum { k_iCallback = k_iSteamGameServerCallbacks + 3 };
	CSteamID m_SteamID;
	EDenyReason m_eDenyReason;
};

// client has been denied to connect to this game server because of a Steam2 auth failure
struct GSClientSteam2Deny_t
{
	enum { k_iCallback = k_iSteamGameServerCallbacks + 4 };
	uint32 m_UserID;
	uint32 m_eSteamError;
};


// client has been accepted by Steam2 to connect to this game server
struct GSClientSteam2Accept_t
{
	enum { k_iCallback = k_iSteamGameServerCallbacks + 5 };
	uint32 m_UserID;
	uint64 m_SteamID;
};

class CSteamGameServer
{
public:
	CSteamGameServer();
	~CSteamGameServer();

	virtual void LogOn(void);
	virtual int LogOn2(void);
	virtual void LogOff(void);
	virtual int LogOff2(void);
	virtual bool BLoggedOn(void);
	virtual void GSSetSpawnCount(unsigned int a1);
	virtual bool GSGetSteam2GetEncryptionKeyToSendToNewClient(void * a1, unsigned int * a2, unsigned int a3);
	virtual bool GSSendSteam2UserConnect(unsigned int a1, void  const* a2, unsigned int a3, unsigned int a4, unsigned short a5, void  const* a6, unsigned int a7);
	virtual bool GSSendSteam3UserConnect(CSteamID a1, unsigned int a2, void  const* a3, unsigned int a4);
	virtual bool GSSendUserConnect(unsigned int a1, unsigned int a2, unsigned short a3, void  const* a4, unsigned int a5);
	virtual bool GSRemoveUserConnect(unsigned int a1);
	virtual bool GSSendUserDisconnect(CSteamID a1, unsigned int a2);
	virtual int GSSendUserStatusResponse(CSteamID a1, int a2, int a3);
	virtual bool GSUpdateStatus(int a1, int a2, int a3, char  const* a4, char  const* a5);
	virtual bool BSecure(void);
	virtual CSteamID GetSteamID(void);
	virtual int GSSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned int a4, char  const* a5, char  const* a6);
	virtual int GSSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned short a4, unsigned short a5, unsigned short a6, char  const* a7, char  const* a8, bool a9);
	virtual bool GSUpdateStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6);
	virtual bool GSCreateUnauthenticatedUser(CSteamID * a1);
	virtual bool GSSetUserData(CSteamID a1, char  const* a2, unsigned int a3);
	virtual void GSUpdateSpectatorPort(unsigned short a1);
	virtual void GSSetGameType(char  const* a1);
	virtual bool BGetUserAchievementStatus(CSteamID a1, char  const* a2);
	virtual int GetGameplayStats(void);
	virtual int RequestUserGroupStatus(CSteamID a1, CSteamID a2);
	virtual int SendUserConnectAndAuthenticate2(unsigned int a1, void  const* a2, unsigned int a3, CSteamID * a4);
	virtual int SendUserConnectAndAuthenticate(CSteamID a1, unsigned int a2, void * a3, unsigned int a4);
	virtual CSteamID CreateUnauthenticatedUserConnection(void);
	virtual int BSetServerType(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned short a5, char  const* a6, char  const* a7, bool a8);
};

CSteamGameServer* GSteamGameServer(void);