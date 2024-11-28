#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUtils002.h"
#include ".\SteamUtils.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUtils* g_pSteamUtils;

CSteamUtils002::CSteamUtils002()
{
}

CSteamUtils002::~CSteamUtils002()
{
}

void CSteamUtils002::GetSecondsSinceAppActive(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetSecondsSinceAppActive(); 
}
void CSteamUtils002::GetSecondsSinceComputerActive(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetSecondsSinceComputerActive(); 
}
EUniverse CSteamUtils002::GetConnectedUniverse(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetConnectedUniverse(); 
}
void CSteamUtils002::GetServerRealTime(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetServerRealTime(); 
}
const char* CSteamUtils002::GetIPCountry(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetIPCountry(); 
}
bool CSteamUtils002::GetImageSize(int a1, unsigned int * a2, unsigned int * a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetImageSize(a1, a2, a3); 
}
bool CSteamUtils002::GetImageRGBA(int a1, unsigned char * a2, int a3)
{
	if (g_bLogging) Logger->Write("%s (%u)\n", __FUNCTION__, a3); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetImageRGBA(a1, a2, a3); 
}
void CSteamUtils002::GetCSERIPPort(unsigned int * a1, unsigned short * a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetCSERIPPort(a1, a2); 
}
void CSteamUtils002::GetCurrentBatteryPower(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetCurrentBatteryPower(); 
}
int CSteamUtils002::GetAppId(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	return 1;
}