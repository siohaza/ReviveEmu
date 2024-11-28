#include "..\Common\steamclientpublic.h"
#include "..\Common\commonincludes.h"
#include ".\SteamUtils.h"

CSteamUtils* g_pSteamUtils;

CSteamUtils* GSteamUtils()
{
	static CSteamUtils g_SteamUtils;
	return &g_SteamUtils;
}

CSteamUtils::CSteamUtils()
{
}

CSteamUtils::~CSteamUtils()
{
}

EUniverse CSteamUtils::GetConnectedUniverse()
{
	return k_EUniversePublic;
}

void CSteamUtils::GetServerRealTime(void)
{
}

const char* CSteamUtils::GetIPCountry(void)
{
	return "Montenegro";
}

void CSteamUtils::GetNumRunningApps(void)
{
}

bool CSteamUtils::GetImageSize(int iAvatar, unsigned int * uWide, unsigned int * uTall)
{
	*uWide = 0;
	*uTall = 0;

	return true;
}

bool CSteamUtils::GetImageRGBA(int iAvatar, unsigned char * rgubDest, int cubImage)
{
	memset(rgubDest, 0, cubImage);
	return false;
}	

void CSteamUtils::SetOfflineMode(bool a1)
{
}

void CSteamUtils::GetOfflineMode(void)
{
}

void CSteamUtils::GetCSERIPPort(unsigned int * a1, unsigned short * a2)
{
	*a1 = 0xffffffff;
	*a2 = 0xffff;
	return;
}

void CSteamUtils::GetSecondsSinceComputerActive(void)
{
}

void CSteamUtils::GetSecondsSinceAppActive(void)
{
}

void CSteamUtils::GetCurrentBatteryPower(void)
{
}

int CSteamUtils::GetAppId()
{
	return 0;
}