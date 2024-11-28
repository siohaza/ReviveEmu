#pragma once

class CSteamClient
{
public:
	CSteamClient();
	~CSteamClient();

	virtual int CreateSteamPipe(void);
	virtual bool BReleaseSteamPipe(HSteamPipe hPipe);
	virtual int ConnectToGlobalUser(HSteamUser hUser);
	virtual HSteamUser CreateLocalUser( HSteamPipe *phSteamPipe );
	virtual void ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser );
	virtual int GetISteamUser( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) ;
	virtual int GetISteamGameServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) ;
	virtual void SetLocalIPBinding( uint32 unIP, uint16 usPort );
	virtual int GetISteamFriends( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion );
	virtual int GetISteamUtils( HSteamPipe hSteamPipe, const char *pchVersion ) ;
	virtual int GetISteamMatchMaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamContentServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamMasterServerUpdater(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamMatchMakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual void GetISteam2Bridge(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual void RunFrame(void);
	virtual int GetIPCCallCount(void);
	virtual int GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual void SetWarningMessageHook(void (*)(int a1, char  const* a2));
	virtual HSteamUser CreateGlobalUser( HSteamPipe *phSteamPipe );
	virtual int GetIVAC( HSteamUser hSteamUser );
	virtual const char* __cdecl	GetUniverseName( EUniverse eUniverse ) ;
	virtual int GetISteamRemoteStorage(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual void GetISteamUserItems(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual void GetISteamGameServerItems(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamBilling( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion );
};

CSteamClient* GSteamClient(void);
int NotifyMissingInterface(const char* pchFunction, const char* pchVersion);