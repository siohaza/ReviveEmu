#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamGameServer002.h"
#include ".\SteamGameServer.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamGameServer* g_pSteamGameServer;

CSteamGameServer002::CSteamGameServer002()
{
}

CSteamGameServer002::~CSteamGameServer002()
{
}

void CSteamGameServer002::LogOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOn(); 
}
void CSteamGameServer002::LogOff(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->LogOff(); 
}
bool CSteamGameServer002::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BLoggedOn(); 
}
void CSteamGameServer002::GSSetSpawnCount(unsigned int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetSpawnCount(a1); 
}
bool CSteamGameServer002::GSGetSteam2GetEncryptionKeyToSendToNewClient(void * a1, unsigned int * a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSGetSteam2GetEncryptionKeyToSendToNewClient(a1, a2, a3); 
}
bool CSteamGameServer002::GSSendSteam2UserConnect(unsigned int a1, void  const* a2, unsigned int a3, unsigned int a4, unsigned short a5, void  const* a6, unsigned int a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendSteam2UserConnect(a1, a2, a3, a4, a5, a6, a7); 
}
bool CSteamGameServer002::GSSendSteam3UserConnect(CSteamID a1, unsigned int a2, void  const* a3, unsigned int a4)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u, %u / %u)\n", __FUNCTION__, a1.m_unAccountID, a2, a4); 
	}
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendSteam3UserConnect(a1, a2, a3, a4); 
}
bool CSteamGameServer002::GSRemoveUserConnect(unsigned int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSRemoveUserConnect(a1); 
}
bool CSteamGameServer002::GSSendUserDisconnect(CSteamID a1, unsigned int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSendUserDisconnect(a1, a2); 
}
int CSteamGameServer002::GSSendUserStatusResponse(CSteamID a1, int a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	//g_pSteamGameServer = GSteamGameServer();
	//return g_pSteamGameServer->GSSendUserStatusResponse(a1, a2, a3); 
	return 0;
}
void CSteamGameServer002::Obsolete_GSSetStatus(int a1, unsigned int a2, int a3, int a4, int a5, int a6, char  const* a7, char  const* a8, char  const* a9, char  const* a10)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	//g_pSteamGameServer = GSteamGameServer();
	//return g_pSteamGameServer->Obsolete_GSSetStatus(); 
}
bool CSteamGameServer002::GSUpdateStatus(int a1, int a2, int a3, char  const* a4, char  const* a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateStatus(a1, a2, a3, a4, a5, NULL); 
}
bool CSteamGameServer002::BSecure(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->BSecure(); 
}
CSteamID CSteamGameServer002::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GetSteamID(); 
}
int CSteamGameServer002::GSSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned int a4, char  const* a5, char  const* a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetServerType(a1, a2, a3, a4, 0, 0, a5, a6, 0); 
}
int CSteamGameServer002::GSSetServerType2(int a1, unsigned int a2, unsigned int a3, unsigned short a4, unsigned short a5, unsigned short a6, char  const* a7, char  const* a8, bool a9)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetServerType(a1, a2, a3, a4, a5, a6, a7, a8, a9); 
}
bool CSteamGameServer002::GSUpdateStatus2(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateStatus(a1, a2, a3, a4, a5, a6); 
}
bool CSteamGameServer002::GSCreateUnauthenticatedUser(CSteamID * a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSCreateUnauthenticatedUser(a1); 
}
bool CSteamGameServer002::GSSetUserData(CSteamID a1, char  const* a2, unsigned int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetUserData(a1, a2, a3); 
}
void CSteamGameServer002::GSUpdateSpectatorPort(unsigned short a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSUpdateSpectatorPort(a1); 
}
void CSteamGameServer002::GSSetGameType(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamGameServer = GSteamGameServer();
	return g_pSteamGameServer->GSSetGameType(a1); 
}
