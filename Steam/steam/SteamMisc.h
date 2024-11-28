#pragma once

extern CLogFile* Logger;
extern BOOL bLogging;

/*
** Misc
*/

STEAM_API void STEAM_CALL SteamClearError(TSteamError *pError)
{
	if(pError)
	{
// #ifdef DEBUG
		//if (bLogging) Logger->Write("SteamClearError\n");
// #endif
		pError->eSteamError = eSteamErrorNone;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
		pError->nDetailedErrorCode = 0;
		pError->szDesc[0] = 0;
	}
	return;
}

STEAM_API int STEAM_CALL InternalSteamNumClientsConnectedToEngine()
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("InternalSteamNumClientsConnectedToEngine\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL InternalSteamShouldShutdownEngine2()
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("InternalSteamShouldShutdownEngine2\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamGetLocalClientVersion(unsigned int* puArg1, unsigned int* puArg2, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamGetLocalClientVersion\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamChangeOfflineStatus(TSteamOfflineStatus* pSteamOfflineStatus, TSteamError* pError)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamChangeOfflineStatus\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamGetOfflineStatus(TSteamOfflineStatus* pSteamOfflineStatus, TSteamError* pError)
{
	if (bLogging) Logger->Write("SteamGetOfflineStatus\n");

	SteamClearError(pError);
	pSteamOfflineStatus->eOfflineNow = 0;
	pSteamOfflineStatus->eOfflineNextSession = 0;
	return 1;
}

STEAM_API SteamCallHandle_t STEAM_CALL SteamUninstall(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamUninstall\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamWeakVerifyNewValveCDKey()
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamWeakVerifyNewValveCDKey\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamGetEncryptedNewValveCDKey()
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamGetEncryptedNewValveCDKey\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamDecryptDataForThisMachine()
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamDecryptDataForThisMachine\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamEncryptDataForThisMachine()
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamEncryptDataForThisMachine\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamFindServersGetErrorString()
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamFindServersGetErrorString\n");
// #endif
	return 0;
}

STEAM_API int STEAM_CALL SteamFindServersIterateServer(int arg1, int arg2, char *szServerAddress, unsigned int uServerAddressChars)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamFindServersIterateServer\n");
// #endif
	if (bSteamDll)
	{
		int retval = 1;
		strcpy(szServerAddress, "empty");
		int (*fptr)(int, int, char*, unsigned int);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamFindServersIterateServer");
		retval = (*fptr)(arg1, arg2, szServerAddress, uServerAddressChars);
		if (bLogging) Logger->Write("\t (%u, %u, %s, %u) %u\n", arg1, arg2, szServerAddress, uServerAddressChars, retval);
		return retval;
	}
	if (arg1 == 3) // CSER Server
	{
		strcpy(szServerAddress, "207.173.177.12:27013");
	}
	else if (arg1 == 4) // Source Servers
	{
		if (arg2 == 0) strcpy(szServerAddress, "72.165.61.189:27011");
		if (arg2 == 1) strcpy(szServerAddress, "69.28.151.162:27011");
		if (arg2 == 2) strcpy(szServerAddress, "68.142.72.250:27011");
		if (arg2 == 3) strcpy(szServerAddress, "72.165.61.190:27011");
	}
	else if (arg1 == 1) // Half-Life Servers
	{
		if (arg2 == 0) strcpy(szServerAddress, "72.165.61.189:27010");
		if (arg2 == 1) strcpy(szServerAddress, "69.28.151.162:27010");
		if (arg2 == 2) strcpy(szServerAddress, "68.142.72.250:27010");
		if (arg2 == 3) strcpy(szServerAddress, "72.165.61.190:27010");
	}

	/*
	MasterServers
	68.142.72.250
	69.28.151.162
	72.165.61.189
	72.165.61.190
	*/

	return 0;
}

STEAM_API int STEAM_CALL SteamFindServersNumServers(unsigned int arg1)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamFindServersNumServers\n");
// #endif
	if (bSteamDll)
	{
		int retval = 1;
		int (*fptr)(unsigned int);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamFindServersNumServers");
		retval = (*fptr)(arg1);
		if (bLogging) Logger->Write("\t (%u) %u\n", arg1, retval);
		return retval;
	}
	switch (arg1)
	{
	case 3: // CSER
		return 1;
	case 4: // HL2
		return 4;
	case 1: // HL1
		return 4;
	default:
		return 0;
	}
}

STEAM_API int STEAM_CALL SteamGetContentServerInfo()
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamGetContentServerInfo\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamSetNotificationCallback(SteamNotificationCallback_t pCallbackFunction, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamSetNotificationCallback\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamWasBlobRegistryDeleted()
{
	return 0;
}

int SteamGetCurrentAppId(unsigned int* puAppId, TSteamError *pError)
{
	return 1;
}

/*
.text:301C5210                 public SteamFindServersNumServers
.text:301C5210 SteamFindServersNumServers proc near    ; CODE XREF: sub_3005C520+5p
.text:301C5210
.text:301C5210 var_14          = dword ptr -14h
.text:301C5210 var_10          = dword ptr -10h
.text:301C5210 var_C           = dword ptr -0Ch
.text:301C5210 var_4           = dword ptr -4
.text:301C5210 arg_0           = dword ptr  8 

	var_4 = 0;
	switch(arg_0)
	{
	case 0x04:
		return 4;
	case 0x03:
		return 1;
	default:
		return 0;
	}
*/