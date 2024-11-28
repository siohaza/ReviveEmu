#pragma once

#include "SteamInterface003.h"
#include "SteamInterface004.h"
#include "SteamInterface005.h"
#include "SteamInterface006.h"
#include "SteamDLLAppsystem001.h"

extern CLogFile* Logger;
extern BOOL bLogging;

STEAM_API unsigned int STEAM_CALL CreateInterface(const char* cszSteamDLLAppsystemInterfaceVersion, TSteamError *pError)
{
	if(bLogging) Logger->Write("CreateInterface(%s)\n", cszSteamDLLAppsystemInterfaceVersion); 
	static CSteamDLLAppsystem001 SteamDLLAppsystem001;

	if(cszSteamDLLAppsystemInterfaceVersion != NULL)
	{
		if(strcmp(cszSteamDLLAppsystemInterfaceVersion,"SteamDLLAppsystem001") == 0)
		{
			SteamClearError(pError);
			return (unsigned int)&SteamDLLAppsystem001;
		}
	}
	return 0;
}

STEAM_API unsigned int STEAM_CALL _f(const char* cszSteamInterfaceVersion)
{
	
	if(cszSteamInterfaceVersion != NULL)
	{
		if(bLogging) Logger->Write("Using Interface %s\n", cszSteamInterfaceVersion);
		if(strcmp(cszSteamInterfaceVersion,"Steam003") == 0)
		{
			static CSteamInterface003 SteamInterface003;
			return (unsigned int)&SteamInterface003;
		}
		else if(strcmp(cszSteamInterfaceVersion,"Steam004") == 0)
		{
			static CSteamInterface004 SteamInterface004;
			return (unsigned int)&SteamInterface004;
		}
		else if(strcmp(cszSteamInterfaceVersion,"Steam005") == 0)
		{
			static CSteamInterface005 SteamInterface005;
			return (unsigned int)&SteamInterface005;
		}
		else if(strcmp(cszSteamInterfaceVersion,"Steam006") == 0)
		{
			static CSteamInterface006 SteamInterface006;
			return (unsigned int)&SteamInterface006;
		}
	}
	return 0;
}