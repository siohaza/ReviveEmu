#include "..\Common\commonincludes.h"
#include ".\steamclientincludes.h"
#include ".\SteamClient.h"

extern bool g_bLogging;
extern CLogFile* Logger;

CSteamClient* g_pSteamClient;

CSteamClient::CSteamClient()
{
}

CSteamClient::~CSteamClient()
{
}

int CSteamClient::CreateSteamPipe()
{ 
	return 1; 
}

bool CSteamClient::BReleaseSteamPipe( HSteamPipe hSteamPipe )
{ 
	return false; 
}

HSteamUser CSteamClient::CreateGlobalUser(int *a1) 
{ 
	*a1 = 1;
	return 1;
}

HSteamUser CSteamClient::ConnectToGlobalUser( HSteamPipe hSteamPipe )
{ 
	return 1; 
}

HSteamUser CSteamClient::CreateLocalUser( HSteamPipe *phSteamPipe )
{ 
	*phSteamPipe = 1; 
	return 1; 
}

void CSteamClient::ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser )
{
}

int CSteamClient::GetISteamUser( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{
	static CSteamUser004 g_SteamUser004;
	static CSteamUser005 g_SteamUser005;
	static CSteamUser006 g_SteamUser006;
	static CSteamUser007 g_SteamUser007;
	static CSteamUser008 g_SteamUser008;
	static CSteamUser009 g_SteamUser009;
	static CSteamUser010 g_SteamUser010;
	static CSteamUser011 g_SteamUser011;

	if (strcmp(pchVersion, "SteamUser004") == 0) return (int)&g_SteamUser004;
	if (strcmp(pchVersion, "SteamUser005") == 0) return (int)&g_SteamUser005;
	if (strcmp(pchVersion, "SteamUser006") == 0) return (int)&g_SteamUser006;
	if (strcmp(pchVersion, "SteamUser007") == 0) return (int)&g_SteamUser007;
	if (strcmp(pchVersion, "SteamUser008") == 0) return (int)&g_SteamUser008;
	if (strcmp(pchVersion, "SteamUser009") == 0) return (int)&g_SteamUser009;
	if (strcmp(pchVersion, "SteamUser010") == 0) return (int)&g_SteamUser010;
	if (strcmp(pchVersion, "SteamUser011") == 0) return (int)&g_SteamUser011;

	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

int CSteamClient::GetIVAC(int a1)
{ 
	static CVAC g_VAC;
	return (int)&g_VAC; 
}

int CSteamClient::GetISteamGameServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) //18h
{
	static CSteamGameServer002 g_SteamGameServer002;
	static CSteamGameServer003 g_SteamGameServer003;
	static CSteamGameServer004 g_SteamGameServer004;
	static CSteamGameServer005 g_SteamGameServer005;
	static CSteamGameServer006 g_SteamGameServer006;
	static CSteamGameServer007 g_SteamGameServer007;

	if (strcmp(pchVersion, "SteamGameServer002") == 0) return (int)&g_SteamGameServer002;
	if (strcmp(pchVersion, "SteamGameServer003") == 0) return (int)&g_SteamGameServer003;
	if (strcmp(pchVersion, "SteamGameServer004") == 0) return (int)&g_SteamGameServer004;
	if (strcmp(pchVersion, "SteamGameServer005") == 0) return (int)&g_SteamGameServer005;
	if (strcmp(pchVersion, "SteamGameServer006") == 0) return (int)&g_SteamGameServer006;
	if (strcmp(pchVersion, "SteamGameServer007") == 0) return (int)&g_SteamGameServer007;

	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

void CSteamClient::SetLocalIPBinding( unsigned int unIP, unsigned short usPort )
{
}

const char* CSteamClient::GetUniverseName(EUniverse) 
{ 
	return "Public";
}

int CSteamClient::GetISteamFriends( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	static CSteamFriends001 g_SteamFriends001;
	static CSteamFriends002 g_SteamFriends002;
	static CSteamFriends003 g_SteamFriends003;
	static CSteamFriends004 g_SteamFriends004;
	static CSteamFriends005 g_SteamFriends005;

	if (strcmp(pchVersion, "SteamFriends001") == 0) return (int)&g_SteamFriends001;
	if (strcmp(pchVersion, "SteamFriends002") == 0) return (int)&g_SteamFriends002;
	if (strcmp(pchVersion, "SteamFriends003") == 0) return (int)&g_SteamFriends003;
	if (strcmp(pchVersion, "SteamFriends004") == 0) return (int)&g_SteamFriends004;
	if (strcmp(pchVersion, "SteamFriends005") == 0) return (int)&g_SteamFriends005;
	
	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

int CSteamClient::GetISteamUtils( HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	static CSteamUtils001 g_SteamUtils001; 
	static CSteamUtils002 g_SteamUtils002; 

	if (strcmp(pchVersion, "SteamUtils001") == 0) return (int)&g_SteamUtils001;
	if (strcmp(pchVersion, "SteamUtils002") == 0) return (int)&g_SteamUtils002;

	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

int CSteamClient::GetISteamBilling(int a1, int a2, char  const* a3) 
{ 
	static CSteamBilling g_SteamBilling;
	return (int)&g_SteamBilling; 
}

int CSteamClient::GetISteamMatchMaking( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	static CSteamMatchMaking001 g_SteamMatchMaking001; 
	static CSteamMatchMaking002 g_SteamMatchMaking002;
	static CSteamMatchMaking003 g_SteamMatchMaking003;
	static CSteamMatchMaking004 g_SteamMatchMaking004;
	static CSteamMatchMaking005 g_SteamMatchMaking005;

	if (strcmp(pchVersion, "SteamMatchMaking001") == 0) return (int)&g_SteamMatchMaking001;
	if (strcmp(pchVersion, "SteamMatchMaking002") == 0) return (int)&g_SteamMatchMaking002;
	if (strcmp(pchVersion, "SteamMatchMaking003") == 0) return (int)&g_SteamMatchMaking003;
	if (strcmp(pchVersion, "SteamMatchMaking004") == 0) return (int)&g_SteamMatchMaking004;
	if (strcmp(pchVersion, "SteamMatchMaking005") == 0) return (int)&g_SteamMatchMaking005;

	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

int CSteamClient::GetISteamApps( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	static CSteamApps001 g_SteamApps001;
	static CSteamApps002 g_SteamApps002;

	if (strcmp(pchVersion, "STEAMAPPS_INTERFACE_VERSION001") == 0) return (int)&g_SteamApps001;
	if (strcmp(pchVersion, "STEAMAPPS_INTERFACE_VERSION002") == 0) return (int)&g_SteamApps002;

	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

int CSteamClient::GetISteamContentServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	static CSteamContentServer g_SteamContentServer;
	return (int)&g_SteamContentServer;
}

int CSteamClient::GetISteamMasterServerUpdater( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	static CSteamMasterServerUpdater001 g_SteamMasterServerUpdater001; 

	if (strcmp(pchVersion, "SteamMasterServerUpdater001") == 0) return (int)&g_SteamMasterServerUpdater001;

	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

int CSteamClient::GetISteamMatchMakingServers( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	static CSteamMatchMakingServers001 g_SteamMatchMakingServers001; 

	if (strcmp(pchVersion, "SteamMatchMakingServers001") == 0) return (int)&g_SteamMatchMakingServers001;

	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

void CSteamClient::RunFrame()
{
}

int CSteamClient::GetIPCCallCount()
{ 
	return 0; 
}

int CSteamClient::GetISteamUserStats( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	static CSteamUserStats001 g_SteamUserStats001;
	static CSteamUserStats002 g_SteamUserStats002;
	static CSteamUserStats003 g_SteamUserStats003;

	if (strcmp(pchVersion, "SteamUserStats001") == 0) return (int)&g_SteamUserStats001;
	if (strcmp(pchVersion, "STEAMUSERSTATS_INTERFACE_VERSION002") == 0) return (int)&g_SteamUserStats002;
	if (strcmp(pchVersion, "STEAMUSERSTATS_INTERFACE_VERSION003") == 0) return (int)&g_SteamUserStats003;
	
	return NotifyMissingInterface(__FUNCTION__, pchVersion);
}

int CSteamClient::GetISteamNetworking(int a1, int a2, char  const* pchVersion)
{ 
	static CSteamNetworking001 g_SteamNetworking001;
	static CSteamNetworking002 g_SteamNetworking002;

	if (strcmp(pchVersion, "SteamNetworking001") == 0) return (int)&g_SteamNetworking001;
	if (strcmp(pchVersion, "SteamNetworking002") == 0) return (int)&g_SteamNetworking002;

	return NotifyMissingInterface(__FUNCTION__, pchVersion);
} 

void CSteamClient::GetISteam2Bridge(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
}

void CSteamClient::SetWarningMessageHook(void(*)(int, const char*))
{
}

int CSteamClient::GetISteamRemoteStorage(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	static CSteamRemoteStorage g_SteamRemoteStorage;
	return (int)&g_SteamRemoteStorage;
}

void CSteamClient::GetISteamUserItems(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
}

void CSteamClient::GetISteamGameServerItems(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
}

CSteamClient* GSteamClient(void)
{
	static CSteamClient g_SteamClient;
	return &g_SteamClient;
}

int NotifyMissingInterface(const char* pchFunction, const char* pchVersion)
{
	char errmsg[255];
	sprintf(errmsg, "%s error: %s not defined! Please update the emulator.\n", pchFunction, pchVersion);
	MessageBoxA(0, errmsg, "Error", 0);
	if (g_bLogging) Logger->Write("ERROR: %s not defined!", pchVersion);
	return 0;
}