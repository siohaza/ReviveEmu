#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamGameServer003.h"
#include ".\SteamGameServer.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamGameServer* g_pSteamGameServer;

CSteamGameServer003::CSteamGameServer003()
{
}

CSteamGameServer003::~CSteamGameServer003()
{
}

void CSteamGameServer003::LogOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOn(); 
}
void CSteamGameServer003::LogOff(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOff(); 
}
bool CSteamGameServer003::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BLoggedOn(); 
}
bool CSteamGameServer003::BSecure(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BSecure(); 
}
CSteamID CSteamGameServer003::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GetSteamID(); 
}
bool CSteamGameServer003::GSGetSteam2GetEncryptionKeyToSendToNewClient(void * a1, unsigned int * a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSGetSteam2GetEncryptionKeyToSendToNewClient(a1, a2, a3); 
}
bool CSteamGameServer003::GSSendUserConnect(unsigned int a1, unsigned int a2, unsigned short a3, void  const* a4, unsigned int a5)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u, %u, %u / %u)\n", __FUNCTION__, a1, a2, a3, a5); 
	}
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendUserConnect(a1, a2, a3, a4, a5); 
}
bool CSteamGameServer003::GSRemoveUserConnect(unsigned int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSRemoveUserConnect(a1); 
}
bool CSteamGameServer003::GSSendUserDisconnect(CSteamID a1, unsigned int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendUserDisconnect(a1, a2); 
}
void CSteamGameServer003::GSSetSpawnCount(unsigned int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetSpawnCount(a1); 
}
int CSteamGameServer003::GSSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned short a4, unsigned short a5, unsigned short a6, char  const* a7, char  const* a8, bool a9)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetServerType(a1, a2, a3, a4, a5, a6, a7, a8, a9); 
}
bool CSteamGameServer003::GSUpdateStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateStatus(a1, a2, a3, a4, a5, a6); 
}
bool CSteamGameServer003::GSCreateUnauthenticatedUser(CSteamID * a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSCreateUnauthenticatedUser(a1); 
}
bool CSteamGameServer003::GSSetUserData(CSteamID a1, char  const* a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetUserData(a1, a2, a3); 
}
void CSteamGameServer003::GSUpdateSpectatorPort(unsigned short a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateSpectatorPort(a1); 
}
void CSteamGameServer003::GSSetGameType(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetGameType(a1); 
}
bool CSteamGameServer003::GSSendSteam2UserConnect(unsigned int a1, void  const* a2, unsigned int a3, unsigned int a4, unsigned short a5, void  const* a6, unsigned int a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendSteam2UserConnect(a1, a2, a3, a4, a5, a6, a7); 
}
bool CSteamGameServer003::GSSendSteam3UserConnect(CSteamID a1, unsigned int a2, void  const* a3, unsigned int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendSteam3UserConnect(a1, a2, a3, a4); 
}
