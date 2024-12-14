#pragma once

#include "SteamEngineClient.h"

extern CLogFile* Logger;
extern char szOrigSteamDll[MAX_PATH];
extern BOOL bSteamDll;
extern BOOL bLogging;
BOOL bSteamStartup = FALSE;

typedef int (STEAM_CALL *SteamStartupCall)(unsigned int, TSteamError*);

/*
** Initialization
*/

STEAM_API int STEAM_CALL SteamStartEngine(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamStartEngine\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamStartup(unsigned int uUsingMask, TSteamError *pError)
{
	if (bLogging) Logger->Write("SteamStartup\n");

	SteamClearError(pError);

	if (!bSteamStartup)
	{
		if (uUsingMask & STEAM_USING_FILESYSTEM)
		{
			bSteamStartup = TRUE;

			if (bSteamFileSystem == true)
			{
				CacheManager = new CCacheFileSystem();

				if (bSteamBlobSystem)
				{
					CBlobFileSystem ClientRegistryBlob;
					if (!ClientRegistryBlob.Open(szBlobFile))
					{
						// Try downloading the CDR using CookieAPI.lib / thanks to steamCooker
						/*initCookieApi();
						int cdrSize;
						char * cdr=downloadContentDescriptionRecord("steam2.steampowered.com",27030,&cdrSize);
						if(!cdr)
						{
						if (bLogging) Logger->Write("Unable to download ContentDescriptionRecord. Falling back to revApps.ini\n");
						return TRUE;
						}
						int ok=importContentDescriptionRecordInBlob("ClientRegistry.blob","/TopKey/ContentDescriptionRecord",cdr,cdrSize);
						if (!ok)
						{
						if (bLogging) Logger->Write("Unable to create ClientRegistry. Falling back to revApps.ini\n");
						return TRUE;
						}
						if (bLogging) Logger->Write("ContentDescriptionRecord successfully downloaded.\n");*/

						if (bLogging) Logger->Write("	Error Initializing Blob Manager ... Advanced Steam Functions Disabled!\n");
						if (bLogging) Logger->Write("	GCF Support from Ini file only!\n");
						bSteamBlobSystem = false;
					}
					else
					{
						if (CBlobNode* CDRNode = ClientRegistryBlob.GetNodeByPath("ContentDescriptionRecord"))
						{
							CDR = new CContentDescriptionRecord(CDRNode->KeyValue->Value);
						}
						else
						{
							if (bLogging) Logger->Write("	Error Locating CDR ... Advanced Steam Functions Disabled!\n");
							if (bLogging) Logger->Write("	GCF Support from Ini file only!\n");
							bSteamBlobSystem = false;
						}
					}

				}
			}
		}
	}

	return 1;
}

STEAM_API int STEAM_CALL SteamCleanup(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamCleanup\n");
// #endif
	SteamClearError(pError);

	if (bSteamFileSystem)
	{
		if (CacheManager)
		{
			delete CacheManager;
			CacheManager = NULL;
		}

		if (CDR)
		{
			delete CDR;
			CDR = NULL;
		}
	}

	bSteamStartup = FALSE;

	return 1;
}

STEAM_API int STEAM_CALL SteamGetVersion(char *szVersion, unsigned int uVersionBufSize)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamGetVersion\n");
// #endif
	int retval = 1;
	if (bSteamDll)
	{
		int (*fptr)(char*, unsigned int);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamGetVersion");
		retval = (*fptr)(szVersion, uVersionBufSize);
		if (bLogging) Logger->Write("\t%u, %s\n", retval, szVersion);
	}
	strcpy(szVersion, "2.0.0.0");
	return retval;
}

STEAM_API int STEAM_CALL SteamShutdownEngine(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamShutdownEngine\n");
// #endif
	return 1;
}