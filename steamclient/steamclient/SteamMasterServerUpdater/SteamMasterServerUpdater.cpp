#include ".\SteamMasterServerUpdater.h"

CSteamMasterServerUpdater* g_pMasterServerUpdater;

CSteamMasterServerUpdater::CSteamMasterServerUpdater()
{
}

CSteamMasterServerUpdater::~CSteamMasterServerUpdater()
{
}

void CSteamMasterServerUpdater::SetActive(bool a1)
{
}
void CSteamMasterServerUpdater::SetHeartbeatInterval(int a1)
{
}
bool CSteamMasterServerUpdater::HandleIncomingPacket(void  const* a1, int a2, unsigned int a3, unsigned short a4)
{
	return true;
}
int CSteamMasterServerUpdater::GetNextOutgoingPacket(void * a1, int a2, unsigned int * a3, unsigned short * a4)
{
	return 0;
}
int CSteamMasterServerUpdater::SetBasicServerData(unsigned short a1, bool a2, char  const* a3, char  const* a4, unsigned short a5, bool a6, char  const* a7)
{
	return 1;
}
void CSteamMasterServerUpdater::ClearAllKeyValues(void)
{
}
int CSteamMasterServerUpdater::SetKeyValue(char  const* a1, char  const* a2)
{
	return 1;
}
void CSteamMasterServerUpdater::NotifyShutdown(void)
{
}
bool CSteamMasterServerUpdater::WasRestartRequested(void)
{
	return false;
}
void CSteamMasterServerUpdater::ForceHeartbeat(void)
{
}
bool CSteamMasterServerUpdater::AddMasterServer(char  const* a1)
{
	return true;
}
bool CSteamMasterServerUpdater::RemoveMasterServer(char  const* a1)
{
	return true;
}
int CSteamMasterServerUpdater::GetNumMasterServers(void)
{
	return 0;
}
bool CSteamMasterServerUpdater::GetMasterServerAddress(int a1, char * a2, int a3)
{
	return true;
}

CSteamMasterServerUpdater* GMasterServerUpdater()
{
	static CSteamMasterServerUpdater g_MasterServerUpdater;
	return &g_MasterServerUpdater;
}