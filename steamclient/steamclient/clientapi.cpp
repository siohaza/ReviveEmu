#include ".\Common\commonincludes.h"
#include ".\Common\steamclientpublic.h"
#include ".\clientapi.h"
#include ".\Common\CriticalSection.h"
#include <vector>
#include ".\SteamClient\SteamClient006.h"
#include ".\SteamClient\SteamClient007.h"

extern CLogFile* Logger;
extern bool g_bLogging;

std::vector<CallbackMsg_t*> g_CallbackMsgList;

CRITICAL_SECTION g_CriticalSection;
static CInitCriticalSection s_InitCriticalSection(&g_CriticalSection);
#define ENTER_CRITICAL_SECTION CEnterCriticalSection ECS(&g_CriticalSection)

STEAMCLIENT_API int __cdecl	CreateInterface(const char* cszInterfaceVersion, unsigned int* arg2)
{	
	static CSteamClient006 g_SteamClient006;
	static CSteamClient007 g_SteamClient007;

	if (arg2) *arg2 = 0;
	if (cszInterfaceVersion != NULL)
	{
		if (g_bLogging) Logger->Write("Using interface %s\n", cszInterfaceVersion);
		if(strcmp(cszInterfaceVersion,"SteamClient006") == 0)
		{
			return (int)&g_SteamClient006;
		}
		if(strcmp(cszInterfaceVersion,"SteamClient007") == 0)
		{	
			return (int)&g_SteamClient007;
		}
	}
	return 0;
}

STEAMCLIENT_API bool Steam_BConnected( HSteamUser hUser, HSteamPipe hSteamPipe )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API bool Steam_BGetCallback( HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg, HSteamCall *phSteamCall )
{
	ENTER_CRITICAL_SECTION;
	if (!g_CallbackMsgList.empty())
	{
		*pCallbackMsg = *g_CallbackMsgList[0];
		if (g_bLogging) 
		{
			Logger->Write("EXPORT: %s (%u)\n", __FUNCTION__, pCallbackMsg->m_iCallback);
		}
		return true;
	}
	return false;
}

STEAMCLIENT_API bool Steam_BLoggedOn( HSteamUser hUser, HSteamPipe hSteamPipe )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API bool Steam_BReleaseSteamPipe( HSteamPipe hSteamPipe )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API HSteamUser Steam_ConnectToGlobalUser( HSteamPipe hSteamPipe )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return 0;
}

STEAMCLIENT_API HSteamUser Steam_CreateGlobalUser( HSteamPipe *phSteamPipe )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	*phSteamPipe = 1;
	return 1;
}

STEAMCLIENT_API HSteamUser Steam_CreateLocalUser( HSteamPipe *phSteamPipe )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	*phSteamPipe = 1;
	return 1;
}

STEAMCLIENT_API HSteamPipe Steam_CreateSteamPipe()
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return 1;
}

STEAMCLIENT_API void Steam_FreeLastCallback( HSteamPipe hSteamPipe )
{
	ENTER_CRITICAL_SECTION;
	if (!g_CallbackMsgList.empty()) g_CallbackMsgList.erase(g_CallbackMsgList.begin());
	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

}

STEAMCLIENT_API bool Steam_GSBLoggedOn( void *phSteamHandle )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API bool Steam_GSBSecure( void *phSteamHandle )
{

	//if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API bool Steam_GSGetSteam2GetEncryptionKeyToSendToNewClient( void *phSteamHandle, void *pvEncryptionKey, uint32 *pcbEncryptionKey, uint32 cbMaxEncryptionKey )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);
	memcpy(pvEncryptionKey, m_key, 160);
	*pcbEncryptionKey = 160;
	return true;
}

STEAMCLIENT_API CSteamID Steam_GSGetSteamID( void *phSteamHandle )
{
	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);
		CSteamID retval;
		retval.m_EAccountType = (EAccountType)0;
		retval.m_EUniverse = (EUniverse)0;
		retval.m_unAccountID = 1337;
		retval.m_unAccountInstance = 0;
		return retval;
	};

STEAMCLIENT_API void Steam_GSLogOff( void *phSteamHandle )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

}

STEAMCLIENT_API void Steam_GSLogOn( void *phSteamHandle )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

}

STEAMCLIENT_API bool Steam_GSRemoveUserConnect( void *phSteamHandle, uint32 unUserID )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API bool Steam_GSSendSteam2UserConnect( void *phSteamHandle, uint32 unUserID, const void *pvRawKey, uint32 unKeyLen, uint32 unIPPublic, uint16 usPort, const void *pvCookie, uint32 cubCookie )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);
	void* test;
	test = malloc(16);
	memset(test, 0x01, 16);
	memcpy((void*)pvCookie, test, 16);

	return true;
}

STEAMCLIENT_API bool Steam_GSSendSteam3UserConnect( void *phSteamHandle, uint64 ulSteamID, uint32 unIPPublic, const void *pvCookie, uint32 cubCookie )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API bool Steam_GSSendUserDisconnect( void *phSteamHandle, uint64 ulSteamID, uint32 unUserID )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API bool Steam_GSSendUserStatusResponse( void *phSteamHandle, uint64 ulSteamID, int nSecondsConnected, int nSecondsSinceLast )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API bool Steam_GSSetServerType( void *phSteamHandle, int32 nAppIdServed, uint32 unServerFlags, uint32 unGameIP, uint32 unGamePort, const char *pchGameDir, const char *pchVersion )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API void Steam_GSSetSpawnCount( void *phSteamHandle, uint32 ucSpawn )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

}

STEAMCLIENT_API bool Steam_GSUpdateStatus( void *phSteamHandle, int cPlayers, int cPlayersMax, int cBotPlayers, const char *pchServerName, const char *pchMapName )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

	return true;
}

STEAMCLIENT_API int Steam_GetGSHandle( HSteamUser hUser, HSteamPipe hSteamPipe )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);
	return 1;
}

STEAMCLIENT_API int Steam_InitiateGameConnection( HSteamUser hUser, HSteamPipe hSteamPipe, void *pBlob, int cbMaxBlob, uint64 steamID, int nGameAppID, uint32 unIPServer, uint16 usPortServer, bool bSecure )
{
	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);
	return 1;
}

STEAMCLIENT_API void Steam_LogOff( HSteamUser hUser, HSteamPipe hSteamPipe )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

}

STEAMCLIENT_API void Steam_LogOn( HSteamUser hUser, HSteamPipe hSteamPipe, uint64 ulSteamID )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

}

STEAMCLIENT_API void Steam_ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

}

STEAMCLIENT_API void Steam_SetLocalIPBinding( uint32 unIP, uint16 usLocalPort )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);

}

STEAMCLIENT_API void Steam_TerminateGameConnection( HSteamUser hUser, HSteamPipe hSteamPipe, uint32 unIPServer, uint16 usPortServer )
{

	if (g_bLogging) Logger->Write("EXPORT: %s\n", __FUNCTION__);
}