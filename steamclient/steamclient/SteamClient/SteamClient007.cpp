#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamClient007.h"
#include ".\SteamClient.h"

extern CSteamClient* g_pSteamClient;

extern bool g_bLogging;
extern CLogFile* Logger;

CSteamClient007::CSteamClient007()
{
}

CSteamClient007::~CSteamClient007()
{
}

int CSteamClient007::CreateSteamPipe(void)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->CreateSteamPipe(); 
} 
bool CSteamClient007::BReleaseSteamPipe(HSteamPipe hPipe)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->BReleaseSteamPipe(hPipe); 
} 
int CSteamClient007::ConnectToGlobalUser(HSteamUser hUser)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->ConnectToGlobalUser(hUser); 
} 
int CSteamClient007::CreateLocalUser(int *arg1)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->CreateLocalUser(arg1); 
} 
void CSteamClient007::ReleaseUser(int a1, int a2)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->ReleaseUser(a1, a2); 
} 
int CSteamClient007::GetISteamUser(int a1, int a2, const char *a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamUser(a1, a2, a3); 
} 
int CSteamClient007::GetISteamGameServer(int a1, int a2, const char *a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamGameServer(a1, a2, a3); 
} 
void CSteamClient007::SetLocalIPBinding(unsigned int a1, unsigned short a2)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->SetLocalIPBinding(a1, a2); 
} 
int CSteamClient007::GetISteamFriends(int a1, int a2, const char *a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamFriends(a1, a2, a3); 
} 
int CSteamClient007::GetISteamUtils(int a1, const char *a2)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a2); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamUtils(a1, a2); 
} 
int CSteamClient007::GetISteamMatchMaking(int a1, int a2, const char *a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamMatchMaking(a1, a2, a3);
} 
int CSteamClient007::GetISteamContentServer(int a1, int a2, const char *a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamContentServer(a1, a2, a3); 
} 
int CSteamClient007::GetISteamMasterServerUpdater(int a1, int a2, const char *a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamMasterServerUpdater(a1, a2, a3);
} 
int CSteamClient007::GetISteamMatchMakingServers(int a1, int a2, const char *a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamMatchMakingServers(a1, a2, a3);
} 
void CSteamClient007::GetISteam2Bridge(int a1, int a2, const char *a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	//g_pSteam2Bridge = GSteam2Bridge();
	//return g_pSteam2Bridge;
} 
void CSteamClient007::RunFrame(void)
{ 
	//if (g_bLogging) Logger->Write("%s\n", __FUNCTION__);*
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->RunFrame(); 
} 
int CSteamClient007::GetIPCCallCount(void)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetIPCCallCount(); 
} 
int CSteamClient007::GetISteamUserStats(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamUserStats(a1, a2, a3); 
} 
int CSteamClient007::GetISteamApps(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamApps(a1, a2, a3); 
} 
int CSteamClient007::GetISteamNetworking(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamNetworking(a1, a2, a3); 
} 
void CSteamClient007::SetWarningMessageHook(void (*)(int, char  const*))
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
} 
void CSteamClient007::CreateGlobalUser(int *a1)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
} 
int CSteamClient007::GetIVAC(int a1)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetIVAC(a1);
} 
const char*	CSteamClient007::GetUniverseName( EUniverse eUniverse )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetUniverseName(eUniverse);
} 
int CSteamClient007::GetISteamRemoteStorage(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamRemoteStorage(a1, a2, a3);
} 
void CSteamClient007::GetISteamUserItems(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
} 
void CSteamClient007::GetISteamGameServerItems(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, a3); 
} 