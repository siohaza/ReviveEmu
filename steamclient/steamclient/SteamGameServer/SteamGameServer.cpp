#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamGameServer.h"
#include <vector>

extern std::vector<CallbackMsg_t*> g_CallbackMsgList;
CSteamGameServer* g_pSteamGameServer;

CSteamGameServer::CSteamGameServer()
{
}

CSteamGameServer::~CSteamGameServer()
{
}

void CSteamGameServer::LogOn(void)
{
}
int CSteamGameServer::LogOn2(void)
{
	return 1;
}
void CSteamGameServer::LogOff(void)
{
}
int CSteamGameServer::LogOff2(void)
{
	return 1;
}
bool CSteamGameServer::BLoggedOn(void)
{
	return true;
}
bool CSteamGameServer::BSecure(void)
{
	return false;
}
CSteamID CSteamGameServer::GetSteamID(void)
{
	CSteamID retval;
	retval.m_EAccountType = (EAccountType)0;
	retval.m_EUniverse = (EUniverse)0;
	retval.m_unAccountID = 1337;
	retval.m_unAccountInstance = 0;
	return retval;
}
void CSteamGameServer::GSSetSpawnCount(unsigned int a1)
{
}
bool CSteamGameServer::GSGetSteam2GetEncryptionKeyToSendToNewClient(void * pvEncryptionKey, unsigned int * pcbEncryptionKey, unsigned int a3)
{
	memcpy(pvEncryptionKey, m_key, 160);
	*pcbEncryptionKey = 160;
	return true;
}
bool CSteamGameServer::GSSendSteam2UserConnect(unsigned int a1, void  const* a2, unsigned int a3, unsigned int a4, unsigned short a5, void  const* a6, unsigned int a7)
{
	return true;
}
bool CSteamGameServer::GSSendSteam3UserConnect(CSteamID a1, unsigned int a2, void  const* a3, unsigned int a4)
{
	return true;
}
bool CSteamGameServer::GSSendUserConnect( uint32 unUserID, uint32 unIPPublic, uint16 usPort, const void *pvCookie, uint32 cubCookie )
{
	memcpy((void*)pvCookie, m_encrypted, sizeof(m_encrypted));



	return true;
}
bool CSteamGameServer::GSRemoveUserConnect(unsigned int a1)
{
	return true;
}
bool CSteamGameServer::GSSendUserDisconnect(CSteamID a1, unsigned int a2)
{
	return true;
}
int CSteamGameServer::GSSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned short a4, unsigned short a5, unsigned short a6, char  const* a7, char  const* a8, bool a9)
{
	return 1;
}
int CSteamGameServer::BSetServerType(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned short a5, char  const* a6, char  const* a7, bool a8)
{
	return 1;
}
bool CSteamGameServer::GSUpdateStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6)
{
	return true;
}
bool CSteamGameServer::GSCreateUnauthenticatedUser(CSteamID * a1)
{
	return true;
}
bool CSteamGameServer::GSSetUserData(CSteamID a1, char  const* a2, unsigned int a3)
{
	return true;
}
void CSteamGameServer::GSUpdateSpectatorPort(unsigned short a1)
{
}
void CSteamGameServer::GSSetGameType(char  const* a1)
{
}
int CSteamGameServer::SendUserConnectAndAuthenticate(CSteamID a1, unsigned int a2, void * a3, unsigned int a4)
{
	return 1;
}
int CSteamGameServer::SendUserConnectAndAuthenticate2(unsigned int a1, void  const* a2, unsigned int a3, CSteamID * a4)
{
	a4->Set(a1*2, k_EUniversePublic, k_EAccountTypeIndividual);
	memset((void*)a2, 0, sizeof(unsigned int));

	return 1;
}
bool CSteamGameServer::BGetUserAchievementStatus(CSteamID a1, char  const* a2)
{
	return false;	
}
CSteamID CSteamGameServer::CreateUnauthenticatedUserConnection(void)
{
	CSteamID test;
	return test;
}
int CSteamGameServer::GetGameplayStats(void)
{
	return 0; 
}

int CSteamGameServer::GSSendUserStatusResponse(CSteamID a1, int a2, int a3)
{
	return 1;
}

bool CSteamGameServer::GSUpdateStatus(int a1, int a2, int a3, const char *a4, const char *a5)
{
	return 1;
}

int CSteamGameServer::GSSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned int a4, const char* a5, const char* a6)
{
	return 1;
}

int CSteamGameServer::RequestUserGroupStatus(CSteamID a1, CSteamID a2)
{
	return 1;
}

CSteamGameServer* GSteamGameServer(void)
{
	static CSteamGameServer g_SteamGameServer;
	return &g_SteamGameServer;
}