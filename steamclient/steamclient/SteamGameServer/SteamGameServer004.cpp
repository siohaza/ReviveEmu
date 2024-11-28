#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamGameServer004.h"
#include ".\SteamGameServer.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamGameServer* g_pSteamGameServer;

CSteamGameServer004::CSteamGameServer004()
{
}

CSteamGameServer004::~CSteamGameServer004()
{
}

void CSteamGameServer004::LogOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOn(); 
}
void CSteamGameServer004::LogOff(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOff(); 
}
bool CSteamGameServer004::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BLoggedOn(); 
}
bool CSteamGameServer004::BSecure(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BSecure(); 
}
CSteamID CSteamGameServer004::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GetSteamID(); 
}
int CSteamGameServer004::SendUserConnectAndAuthenticate(CSteamID a1, unsigned int a2, void * a3, unsigned int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->SendUserConnectAndAuthenticate(a1, a2, a3, a4); 
}
CSteamID CSteamGameServer004::CreateUnauthenticatedUserConnection(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->CreateUnauthenticatedUserConnection(); 
}
bool CSteamGameServer004::GSSendUserDisconnect(CSteamID a1, unsigned int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendUserDisconnect(a1, a2); 
}
bool CSteamGameServer004::BUpdateUserData(CSteamID a1, char  const* a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetUserData(a1, a2, a3); 
}
int CSteamGameServer004::BSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned short a4, unsigned short a5, unsigned short a6, char  const* a7, char  const* a8, bool a9)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetServerType(a1, a2, a3, a4, a5, a6, a7, a8, a9); 
}
bool CSteamGameServer004::UpdateServerStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateStatus(a1, a2, a3, a4, a5, a6); 
}
void CSteamGameServer004::UpdateSpectatorPort(unsigned short a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateSpectatorPort(a1); 
}
void CSteamGameServer004::SetGameType(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetGameType(a1); 
}
bool CSteamGameServer004::BGetUserAchievementStatus(CSteamID a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BGetUserAchievementStatus(a1, a2); 
}