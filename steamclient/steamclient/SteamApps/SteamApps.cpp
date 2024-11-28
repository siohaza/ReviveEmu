#include "..\Common\commonincludes.h"
#include ".\SteamApps.h"

CSteamApps* g_pSteamApps;
extern char g_chLang[20];

CSteamApps::CSteamApps()
{
}

CSteamApps::~CSteamApps()
{
}

int CSteamApps::GetAppData( uint32 nAppID, const char *pchKey, char *pchValue, int cchValueMax ) 
	{ 
		if (strcmp(pchKey, "subscribed") == 0) 
		{
			*pchValue = '1'; 
		}
		else
			strcpy(pchValue, "");

		return 1;
	}
bool CSteamApps::BIsSubscribed(void)
	{
		return true;
	}
bool CSteamApps::BIsLowViolence(void)
{
		return false;
}
bool CSteamApps::BIsCybercafe(void)
{
		return false;
}
bool CSteamApps::BIsVACBanned(void)
{
		return false;
}
unsigned char* CSteamApps::GetCurrentGameLanguage(void)
{
	return (unsigned char*)g_chLang;
}
unsigned char* CSteamApps::GetAvailableGameLanguages(void)
{
	return (unsigned char*)g_chLang;
}
bool CSteamApps::BIsSubscribedApp(unsigned int a1)
{
	return true;
}

CSteamApps* GSteamApps(void)
{
	static CSteamApps g_SteamApps;
	return &g_SteamApps;
}
