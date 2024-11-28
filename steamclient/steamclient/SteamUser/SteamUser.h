#pragma once

#include "..\Common\steamclientpublic.h"

//-----------------------------------------------------------------------------
// Purpose: called when a logon attempt has succeeded
//-----------------------------------------------------------------------------
struct LogonSuccess_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 1 };
};


//-----------------------------------------------------------------------------
// Purpose: called when a logon attempt has failed
//-----------------------------------------------------------------------------
struct LogonFailure_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 2 };
	EResult m_eResult;
};


//-----------------------------------------------------------------------------
// Purpose: called when the user logs off
//-----------------------------------------------------------------------------
struct LoggedOff_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 3 };
	EResult m_eResult;
};


//-----------------------------------------------------------------------------
// Purpose: called when the client is trying to retry logon after being unintentionally logged off
//-----------------------------------------------------------------------------
struct BeginLogonRetry_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 4 };
};


//-----------------------------------------------------------------------------
// Purpose: connect to game server denied
//-----------------------------------------------------------------------------
struct ClientGameServerDeny_t
{
	enum { k_iCallback = k_iSteamUserCallbacks + 13 };

	uint32 m_uAppID;
	uint32 m_unGameServerIP;
	uint16 m_usGameServerPort;
	uint16 m_bSecure;
	uint32 m_uReason;
};

enum ERegistrySubTree
{
	k_ERegistrySubTreeNews = 0,
	k_ERegistrySubTreeApps = 1,
	k_ERegistrySubTreeSubscriptions = 2,
	k_ERegistrySubTreeGameServers = 3,
	k_ERegistrySubTreeFriends = 4,
	k_ERegistrySubTreeSystem = 5,
};

enum EAppUsageEvent
{
	k_EAppUsageEventGameLaunch = 1,
	k_EAppUsageEventGameLaunchTrial = 2,
	k_EAppUsageEventMedia = 3,
	k_EAppUsageEventPreloadStart = 4,
	k_EAppUsageEventPreloadFinish = 5,
	k_EAppUsageEventMarketingMessageView = 6,	// deprecated, do not use
	k_EAppUsageEventInGameAdViewed = 7,
	k_EAppUsageEventGameLaunchFreeWeekend = 8,
};

class CSteamUser
{
public:
	CSteamUser();
	~CSteamUser();

	virtual HSteamUser GetHSteamUser(void);
	virtual void LogOn(CSteamID a1);
	virtual void LogOff(void);
	virtual bool BLoggedOn(void);
	virtual void GetLogonState(void);
	virtual bool BConnected(void);
	virtual CSteamID GetSteamID(void);
	virtual bool IsVACBanned(int a1);
	virtual void RequireShowVACBannedMessage(int a1);
	virtual void AcknowledgeVACBanning(int a1);
	virtual int NClientGameIDAdd(int a1);
	virtual int RemoveClientGame(int a1);
	virtual void SetClientGameServer(int a1, unsigned int a2, unsigned short a3);
	virtual void SetSteam2Ticket(unsigned char * a1, int a2);
	virtual void AddServerNetAddress(unsigned int a1, unsigned short a2);
	virtual void SetEmail(char  const* a1);
	virtual int GetSteamGameConnectToken(void * a1, int a2);
	virtual void SetRegistryString(ERegistrySubTree a1, char  const* a2, char  const* a3);
	virtual void GetRegistryString(ERegistrySubTree a1, char  const* a2, char * a3, int a4);
	virtual void SetRegistryInt(ERegistrySubTree a1, char  const* a2, int a3);
	virtual void GetRegistryInt(ERegistrySubTree a1, char  const* a2, int * a3);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7, void * a8, int a9);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, unsigned int a4, unsigned short a5, bool a6);
	virtual void TerminateGameConnection(unsigned int a1, unsigned short a2);
	virtual void SetSelfAsPrimaryChatDestination(void);
	virtual void IsPrimaryChatDestination(void);
	virtual void RequestLegacyCDKey(unsigned int a1);
	virtual void SendGuestPassByEmail(char  const* a1, unsigned long long a2, bool a3);
	virtual void SendGuestPassByAccountID(unsigned int a1, unsigned long long a2, bool a3);
	virtual void AckGuestPass(char  const* a1);
	virtual void RedeemGuestPass(char  const* a1);
	virtual void GetGuestPassToGiveCount(void);
	virtual void GetGuestPassToRedeemCount(void);
	virtual void GetGuestPassLastUpdateTime(void);
	virtual void GetGuestPassToGiveInfo(unsigned int a1, unsigned long long * a2, int * a3, unsigned int * a4, unsigned int * a5, unsigned int * a6, unsigned int * a7, char * a8, int a9);
	virtual void GetGuestPassToRedeemInfo(unsigned int a1, unsigned long long * a2, int * a3, unsigned int * a4, unsigned int * a5, unsigned int * a6, unsigned int * a7);
	virtual void GetGuestPassToRedeemSenderAddress(unsigned int a1, char * a2, int a3);
	virtual void GetGuestPassToRedeemSenderName(unsigned int a1, char * a2, int a3);
	virtual void AcknowledgeMessageByGID(char  const* a1);
	virtual void SetLanguage(char  const* a1);
	virtual void TrackAppUsageEvent(CGameID a1, int a2, char  const* a3);
	virtual void SetAccountName(char  const* a1);
	virtual void SetPassword(char  const* a1);
	virtual void SetAccountCreationTime(unsigned int a1);
	virtual void RefreshSteam2Login(void);
	virtual int GetUserDataFolder(char * a1, int a2);
	virtual int StartVoiceRecording(void);
	virtual int StopVoiceRecording(void);
	virtual int GetCompressedVoice(void * a1, unsigned int a2, unsigned int * a3);
	virtual int DecompressVoice(void * a1, unsigned int a2, void * a3, unsigned int a4, unsigned int * a5);
};

CSteamUser* GSteamUser(void);