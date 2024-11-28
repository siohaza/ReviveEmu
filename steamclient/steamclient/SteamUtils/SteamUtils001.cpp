#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUtils001.h"
#include ".\SteamUtils.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUtils* g_pSteamUtils;

CSteamUtils001::CSteamUtils001()
{
}

CSteamUtils001::~CSteamUtils001()
{
}

void CSteamUtils001::GetSecondsSinceAppActive(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetSecondsSinceAppActive(); 
}
void CSteamUtils001::GetSecondsSinceComputerActive(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetSecondsSinceComputerActive(); 
}
EUniverse CSteamUtils001::GetConnectedUniverse(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetConnectedUniverse(); 
}
void CSteamUtils001::GetServerRealTime(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetServerRealTime(); 
}
const char* CSteamUtils001::GetIPCountry(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetIPCountry(); 
}
bool CSteamUtils001::GetImageSize(int a1, unsigned int * a2, unsigned int * a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetImageSize(a1, a2, a3); 
}
bool CSteamUtils001::GetImageRGBA(int a1, unsigned char * a2, int a3)
{
	if (g_bLogging) Logger->Write("%s (%u)\n", __FUNCTION__, a3); 
	g_pSteamUtils = GSteamUtils();
	return g_pSteamUtils->GetImageRGBA(a1, a2, a3); 
}
