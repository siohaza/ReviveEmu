#include ".\SteamNetworking001.h"
#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"

extern bool g_bLogging;
extern CLogFile* Logger;

CSteamNetworking001::CSteamNetworking001()
{
}

CSteamNetworking001::~CSteamNetworking001()
{
}

void CSteamNetworking001::CreateListenSocket(int, uint, ushort)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::CreateP2PConnectionSocket(CSteamID, int, int)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::CreateConnectionSocket(unsigned int, unsigned short, int)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::DestroySocket(unsigned int, bool)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::DestroyListenSocket(unsigned int, bool)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::SendDataOnSocket(unsigned int, void *, unsigned int, bool)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::IsDataAvailableOnSocket(unsigned int, unsigned int *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::RetrieveDataFromSocket(unsigned int, void *, unsigned int, unsigned int *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::IsDataAvailable(unsigned int, unsigned int *, unsigned int *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::RetrieveData(unsigned int, void *, unsigned int, unsigned int *, unsigned int *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::GetSocketInfo(unsigned int, CSteamID *, int *, unsigned int *, unsigned short *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamNetworking001::GetListenSocketInfo(unsigned int, unsigned int *, unsigned short *)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}