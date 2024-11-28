#include ".\SteamNetworking002.h"
#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"

extern bool g_bLogging;
extern CLogFile* Logger;

CSteamNetworking002::CSteamNetworking002()
{
}

CSteamNetworking002::~CSteamNetworking002()
{
}

void CSteamNetworking002::CreateListenSocket(int, uint, ushort, bool)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::CreateP2PConnectionSocket(CSteamID, int, int, bool)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::CreateConnectionSocket(unsigned int, unsigned short, int)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::DestroySocket(unsigned int, bool)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::DestroyListenSocket(unsigned int, bool)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::SendDataOnSocket(unsigned int, void *, unsigned int, bool)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::IsDataAvailableOnSocket(unsigned int, unsigned int *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::RetrieveDataFromSocket(unsigned int, void *, unsigned int, unsigned int *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::IsDataAvailable(unsigned int, unsigned int *, unsigned int *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::RetrieveData(unsigned int, void *, unsigned int, unsigned int *, unsigned int *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::GetSocketInfo(unsigned int, CSteamID *, int *, unsigned int *, unsigned short *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::GetListenSocketInfo(unsigned int, unsigned int *, unsigned short *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::GetSocketConnectionType(unsigned int)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking002::GetMaxPacketSize(unsigned int)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
