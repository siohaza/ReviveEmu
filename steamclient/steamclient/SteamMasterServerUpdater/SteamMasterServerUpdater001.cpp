#include "..\Common\commonincludes.h"
#include ".\SteamMasterServerUpdater001.h"
#include ".\SteamMasterServerUpdater.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamMasterServerUpdater* g_pMasterServerUpdater;

CSteamMasterServerUpdater001::CSteamMasterServerUpdater001()
{
}

CSteamMasterServerUpdater001::~CSteamMasterServerUpdater001()
{
}

void CSteamMasterServerUpdater001::SetActive(bool a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->SetActive(a1); 
}
void CSteamMasterServerUpdater001::SetHeartbeatInterval(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->SetHeartbeatInterval(a1); 
}
bool CSteamMasterServerUpdater001::HandleIncomingPacket(void  const* a1, int a2, unsigned int a3, unsigned short a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->HandleIncomingPacket(a1, a2, a3, a4); 
}
int CSteamMasterServerUpdater001::GetNextOutgoingPacket(void * a1, int a2, unsigned int * a3, unsigned short * a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->GetNextOutgoingPacket(a1, a2, a3, a4); 
}
int CSteamMasterServerUpdater001::SetBasicServerData(unsigned short a1, bool a2, char  const* a3, char  const* a4, unsigned short a5, bool a6, char  const* a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->SetBasicServerData(a1, a2, a3, a4, a5, a6, a7); 
}
void CSteamMasterServerUpdater001::ClearAllKeyValues(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->ClearAllKeyValues(); 
}
int CSteamMasterServerUpdater001::SetKeyValue(char  const* a1, char  const* a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->SetKeyValue(a1, a2); 
}
void CSteamMasterServerUpdater001::NotifyShutdown(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->NotifyShutdown(); 
}
bool CSteamMasterServerUpdater001::WasRestartRequested(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->WasRestartRequested(); 
}
void CSteamMasterServerUpdater001::ForceHeartbeat(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->ForceHeartbeat(); 
}
bool CSteamMasterServerUpdater001::AddMasterServer(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->AddMasterServer(a1); 
}
bool CSteamMasterServerUpdater001::RemoveMasterServer(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->RemoveMasterServer(a1); 
}
int CSteamMasterServerUpdater001::GetNumMasterServers(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->GetNumMasterServers(); 
}
bool CSteamMasterServerUpdater001::GetMasterServerAddress(int a1, char * a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pMasterServerUpdater = GMasterServerUpdater();
	return g_pMasterServerUpdater->GetMasterServerAddress(a1, a2, a3); 
}
