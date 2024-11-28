#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamApps002.h"
#include ".\SteamApps.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamApps* g_pSteamApps;

CSteamApps002::CSteamApps002()
{
}

CSteamApps002::~CSteamApps002()
{
}

bool CSteamApps002::BIsSubscribed(void)
{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__);
		g_pSteamApps = GSteamApps();
		return g_pSteamApps->BIsSubscribed();
}
bool CSteamApps002::BIsLowViolence(void)
{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__);
		g_pSteamApps = GSteamApps();
		return g_pSteamApps->BIsLowViolence();
}
bool CSteamApps002::BIsCybercafe(void)
{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__);
		g_pSteamApps = GSteamApps();
		return g_pSteamApps->BIsCybercafe();
}
bool CSteamApps002::BIsVACBanned(void)
{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__);
		g_pSteamApps = GSteamApps();
		return g_pSteamApps->BIsVACBanned();
}
unsigned char* CSteamApps002::GetCurrentGameLanguage(void)
{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__);
		g_pSteamApps = GSteamApps();
		return g_pSteamApps->GetCurrentGameLanguage();
}
unsigned char* CSteamApps002::GetAvailableGameLanguages(void)
{
		if (g_bLogging) Logger->Write("%s\n", __FUNCTION__);
		g_pSteamApps = GSteamApps();
		return g_pSteamApps->GetAvailableGameLanguages();
}
bool CSteamApps002::BIsSubscribedApp(unsigned int a1)
{
		if (g_bLogging) Logger->Write("%s (%u)\n", __FUNCTION__, a1);
		g_pSteamApps = GSteamApps();
		return g_pSteamApps->BIsSubscribedApp(a1);
}

