#include ".\SteamRemoteStorage.h"
#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"

extern bool g_bLogging;
extern CLogFile* Logger;

CSteamRemoteStorage::CSteamRemoteStorage()
{
}

CSteamRemoteStorage::~CSteamRemoteStorage()
{
}

void CSteamRemoteStorage::FileWrite(char  const* pchFileName, void  const* pvData, int iBytes)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, pchFileName); 
}
void CSteamRemoteStorage::GetFileSize(char  const* pchFileName)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, pchFileName); 
}
void CSteamRemoteStorage::FileRead(char  const* pchFileName, void * pvData, int iBytes)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, pchFileName); 
}
void CSteamRemoteStorage::FileExists(char  const* pchFileName)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, pchFileName); 
}
void CSteamRemoteStorage::FileDelete(char  const* pchFileName)
{
	if (g_bLogging) Logger->Write("%s (%s)\n", __FUNCTION__, pchFileName); 
}
void CSteamRemoteStorage::GetFileCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamRemoteStorage::GetFileNameAndSize(int, int * piSize)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
void CSteamRemoteStorage::GetQuota(int * a1, int * a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
}
