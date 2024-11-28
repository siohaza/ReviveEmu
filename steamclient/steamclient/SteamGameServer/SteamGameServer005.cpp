#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamGameServer005.h"
#include ".\SteamGameServer.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamGameServer* g_pSteamGameServer;

CSteamGameServer005::CSteamGameServer005()
{
}

CSteamGameServer005::~CSteamGameServer005()
{
}

int CSteamGameServer005::LogOn(void)
{
	if (g_bLogging) Logger->Write("logon %s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOn2(); 
}
int CSteamGameServer005::LogOff(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOff2(); 
}
bool CSteamGameServer005::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BLoggedOn(); 
}
bool CSteamGameServer005::BSecure(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BSecure(); 
}
CSteamID CSteamGameServer005::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GetSteamID(); 
}
int CSteamGameServer005::SendUserConnectAndAuthenticate(unsigned int a1, void  const* a2, unsigned int a3, CSteamID * a4)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u, 0x%08X, %u)\n", __FUNCTION__, a1, a2, a3);
	}

	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->SendUserConnectAndAuthenticate2(a1, a2, a3, a4); 
}
CSteamID CSteamGameServer005::CreateUnauthenticatedUserConnection(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->CreateUnauthenticatedUserConnection(); 
}
bool CSteamGameServer005::GSSendUserDisconnect(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendUserDisconnect(a1, 0); 
}
bool CSteamGameServer005::BUpdateUserData(CSteamID a1, char  const* a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetUserData(a1, a2, a3); 
}
int CSteamGameServer005::BSetServerType(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned short a5, char  const* a6, char  const* a7, bool a8)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BSetServerType(a1, a2, a3, a4, a5, a6, a7, a8); 
}
bool CSteamGameServer005::UpdateServerStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateStatus(a1, a2, a3, a4, a5, a6); 
}
void CSteamGameServer005::UpdateSpectatorPort(unsigned short a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateSpectatorPort(a1); 
}
void CSteamGameServer005::SetGameType(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetGameType(a1); 
}
bool CSteamGameServer005::BGetUserAchievementStatus(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BGetUserAchievementStatus(a1, a2); 
}
int CSteamGameServer005::GetGameplayStats(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GetGameplayStats(); 
}

