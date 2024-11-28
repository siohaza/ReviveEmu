#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamGameServer006.h"
#include ".\SteamGameServer.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamGameServer* g_pSteamGameServer;

CSteamGameServer006::CSteamGameServer006()
{
}

CSteamGameServer006::~CSteamGameServer006()
{
}

int CSteamGameServer006::LogOn(void)
{
	if (g_bLogging) Logger->Write("logon %s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOn2(); 
}
int CSteamGameServer006::LogOff(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOff2(); 
}
bool CSteamGameServer006::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BLoggedOn(); 
}
bool CSteamGameServer006::BSecure(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BSecure(); 
}
CSteamID CSteamGameServer006::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GetSteamID(); 
}
int CSteamGameServer006::SendUserConnectAndAuthenticate(unsigned int a1, void  const* a2, unsigned int a3, CSteamID * a4)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u, 0x%08X, %u)\n", __FUNCTION__, a1, a2, a3);
	}

	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->SendUserConnectAndAuthenticate2(a1, a2, a3, a4); 
}
CSteamID CSteamGameServer006::CreateUnauthenticatedUserConnection(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->CreateUnauthenticatedUserConnection(); 
}
bool CSteamGameServer006::GSSendUserDisconnect(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendUserDisconnect(a1, 0); 
}
bool CSteamGameServer006::BUpdateUserData(CSteamID a1, char  const* a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetUserData(a1, a2, a3); 
}
int CSteamGameServer006::BSetServerType(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned short a5, char  const* a6, char  const* a7, bool a8)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BSetServerType(a1, a2, a3, a4, a5, a6, a7, a8); 
}
bool CSteamGameServer006::UpdateServerStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateStatus(a1, a2, a3, a4, a5, a6); 
}
void CSteamGameServer006::UpdateSpectatorPort(unsigned short a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateSpectatorPort(a1); 
}
void CSteamGameServer006::SetGameType(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetGameType(a1); 
}
bool CSteamGameServer006::BGetUserAchievementStatus(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BGetUserAchievementStatus(a1, a2); 
}
int CSteamGameServer006::GetGameplayStats(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GetGameplayStats(); 
}