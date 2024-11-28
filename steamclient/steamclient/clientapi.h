#ifdef STEAMCLIENT_EXPORTS
#define STEAMCLIENT_API __declspec(dllexport)
#else
#define STEAMCLIENT_API __declspec(dllimport)
#endif

// Warning: 'Steam_GSGetSteamID' has C-linkage specified, but returns UDT 'CSteamID' which is incompatible with C
#pragma warning(disable:4190) 


	STEAMCLIENT_API int __cdecl	CreateInterface(const char* cszInterfaceVersion, unsigned int* arg2);
	STEAMCLIENT_API bool Steam_BConnected( HSteamUser hUser, HSteamPipe hSteamPipe );
	STEAMCLIENT_API bool Steam_BGetCallback( HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg, HSteamCall *phSteamCall );
	STEAMCLIENT_API bool Steam_BLoggedOn( HSteamUser hUser, HSteamPipe hSteamPipe );
	STEAMCLIENT_API bool Steam_BReleaseSteamPipe( HSteamPipe hSteamPipe );
	STEAMCLIENT_API HSteamUser Steam_ConnectToGlobalUser( HSteamPipe hSteamPipe );
	STEAMCLIENT_API HSteamUser Steam_CreateGlobalUser( HSteamPipe *phSteamPipe );
	STEAMCLIENT_API HSteamUser Steam_CreateLocalUser( HSteamPipe *phSteamPipe );
	STEAMCLIENT_API HSteamPipe Steam_CreateSteamPipe();
	STEAMCLIENT_API void Steam_FreeLastCallback( HSteamPipe hSteamPipe );
	STEAMCLIENT_API bool Steam_GSBLoggedOn( void *phSteamHandle );
	STEAMCLIENT_API bool Steam_GSBSecure( void *phSteamHandle );
	STEAMCLIENT_API bool Steam_GSGetSteam2GetEncryptionKeyToSendToNewClient( void *phSteamHandle, void *pvEncryptionKey, uint32 *pcbEncryptionKey, uint32 cbMaxEncryptionKey );
	STEAMCLIENT_API CSteamID Steam_GSGetSteamID( void *phSteamHandle );
	STEAMCLIENT_API void Steam_GSLogOff( void *phSteamHandle );
	STEAMCLIENT_API void Steam_GSLogOn( void *phSteamHandle );
	STEAMCLIENT_API bool Steam_GSRemoveUserConnect( void *phSteamHandle, uint32 unUserID );
	STEAMCLIENT_API bool Steam_GSSendSteam2UserConnect( void *phSteamHandle, uint32 unUserID, const void *pvRawKey, uint32 unKeyLen, uint32 unIPPublic, uint16 usPort, const void *pvCookie, uint32 cubCookie );
	STEAMCLIENT_API bool Steam_GSSendSteam3UserConnect( void *phSteamHandle, uint64 ulSteamID, uint32 unIPPublic, const void *pvCookie, uint32 cubCookie );
	STEAMCLIENT_API bool Steam_GSSendUserDisconnect( void *phSteamHandle, uint64 ulSteamID, uint32 unUserID );
	STEAMCLIENT_API bool Steam_GSSendUserStatusResponse( void *phSteamHandle, uint64 ulSteamID, int nSecondsConnected, int nSecondsSinceLast );
	STEAMCLIENT_API bool Steam_GSSetServerType( void *phSteamHandle, int32 nAppIdServed, uint32 unServerFlags, uint32 unGameIP, uint32 unGamePort, const char *pchGameDir, const char *pchVersion );
	STEAMCLIENT_API void Steam_GSSetSpawnCount( void *phSteamHandle, uint32 ucSpawn );
	STEAMCLIENT_API bool Steam_GSUpdateStatus( void *phSteamHandle, int cPlayers, int cPlayersMax, int cBotPlayers, const char *pchServerName, const char *pchMapName );
	STEAMCLIENT_API int Steam_GetGSHandle( HSteamUser hUser, HSteamPipe hSteamPipe );
	STEAMCLIENT_API int Steam_InitiateGameConnection( HSteamUser hUser, HSteamPipe hSteamPipe, void *pBlob, int cbMaxBlob, uint64 steamID, int nGameAppID, uint32 unIPServer, uint16 usPortServer, bool bSecure );
	STEAMCLIENT_API void Steam_LogOff( HSteamUser hUser, HSteamPipe hSteamPipe );
	STEAMCLIENT_API void Steam_LogOn( HSteamUser hUser, HSteamPipe hSteamPipe, uint64 ulSteamID );
	STEAMCLIENT_API void Steam_ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser );
	STEAMCLIENT_API void Steam_SetLocalIPBinding( uint32 unIP, uint16 usLocalPort );
	STEAMCLIENT_API void Steam_TerminateGameConnection( HSteamUser hUser, HSteamPipe hSteamPipe, uint32 unIPServer, uint16 usPortServer );
