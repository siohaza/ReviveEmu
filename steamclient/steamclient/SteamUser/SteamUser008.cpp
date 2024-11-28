#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUser008.h"
#include ".\SteamUser.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUser* g_pSteamUser;

CSteamUser008::CSteamUser008()
{
}

CSteamUser008::~CSteamUser008()
{
}

HSteamUser CSteamUser008::GetHSteamUser(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetHSteamUser(); 
}
bool CSteamUser008::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->BLoggedOn(); 
}
CSteamID CSteamUser008::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetSteamID(); 
}
int CSteamUser008::InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7, void * a8, int a9)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u / %u, %u, %u, %u, %u)\n", __FUNCTION__, a2, a3.m_unAccountID, a4.AppID(), a5, a6, a7); 
	}
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->InitiateGameConnection(a1, a2, a3, a4, a5, a6, a7, a8, a9); 
}
void CSteamUser008::TerminateGameConnection(unsigned int a1, unsigned short a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TerminateGameConnection(a1, a2); 
}
void CSteamUser008::TrackAppUsageEvent(CGameID a1, int a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TrackAppUsageEvent(a1, a2, a3); 
}
void CSteamUser008::RefreshSteam2Login(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->RefreshSteam2Login(); 
}
