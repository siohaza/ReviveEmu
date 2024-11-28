#pragma once

#include "..\Common\steamclientpublic.h"

class CSteamClient006
{
public:
	CSteamClient006();
	~CSteamClient006();

	virtual HSteamPipe CreateSteamPipe();
	virtual bool BReleaseSteamPipe( HSteamPipe hSteamPipe );
	virtual HSteamUser CreateGlobalUser( HSteamPipe *phSteamPipe );
	virtual HSteamUser ConnectToGlobalUser( HSteamPipe hSteamPipe );
	virtual HSteamUser CreateLocalUser( HSteamPipe *phSteamPipe );
	virtual void ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser );
	virtual int GetISteamUser( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) ;
	virtual int GetIVAC( HSteamUser hSteamUser );
	virtual int GetISteamGameServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) ;
	virtual void SetLocalIPBinding( uint32 unIP, uint16 usPort );
	virtual const char* __cdecl	GetUniverseName( EUniverse eUniverse ) ;
	virtual int GetISteamFriends( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion );
	virtual int GetISteamUtils( HSteamPipe hSteamPipe, const char *pchVersion ) ;
	virtual int GetISteamBilling( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion );
	virtual int GetISteamMatchMaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamContentServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamMasterServerUpdater(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual int GetISteamMatchMakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char  const* pchVersion);
	virtual void RunFrame(void);
	virtual int GetIPCCallCount(void);
};