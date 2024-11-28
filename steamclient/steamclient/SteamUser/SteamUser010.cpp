#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUser010.h"
#include ".\SteamUser.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUser* g_pSteamUser;

CSteamUser010::CSteamUser010()
{
}

CSteamUser010::~CSteamUser010()
{
}

HSteamUser CSteamUser010::GetHSteamUser(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetHSteamUser(); 
}
bool CSteamUser010::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->BLoggedOn(); 
}
CSteamID CSteamUser010::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetSteamID(); 
}
int CSteamUser010::InitiateGameConnection(void * a1, int a2, CSteamID a3, unsigned int a4, unsigned short a5, bool a6)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u / %u, %u, %u, %u, %u)\n", __FUNCTION__, a2, a3.m_unAccountID, a4, a5, a6); 
	}
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->InitiateGameConnection(a1, a2, a3, a4, a5, a6); 
}
void CSteamUser010::TerminateGameConnection(unsigned int a1, unsigned short a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TerminateGameConnection(a1, a2); 
}
void CSteamUser010::TrackAppUsageEvent(CGameID a1, int a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TrackAppUsageEvent(a1, a2, a3); 
}
