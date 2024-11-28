#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamApps001.h"
#include ".\SteamApps.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamApps* g_pSteamApps;

CSteamApps001::CSteamApps001()
{
}

CSteamApps001::~CSteamApps001()
{
}

int CSteamApps001::GetAppData(unsigned int a1, char  const* a2, char * a3, int a4)
{
	if (g_bLogging) Logger->Write("%s (%u / %s)\n", __FUNCTION__, a1, a2);
	g_pSteamApps = GSteamApps();
	return g_pSteamApps->GetAppData(a1, a2, a3, a4);
};
