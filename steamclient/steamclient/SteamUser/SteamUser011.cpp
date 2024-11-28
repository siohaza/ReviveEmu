#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUser011.h"
#include ".\SteamUser.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUser* g_pSteamUser;

CSteamUser011::CSteamUser011()
{
}

CSteamUser011::~CSteamUser011()
{
}

HSteamUser CSteamUser011::GetHSteamUser(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetHSteamUser(); 
}
bool CSteamUser011::BLoggedOn(void)
{
	//if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->BLoggedOn(); 
}
CSteamID CSteamUser011::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetSteamID(); 
}
int CSteamUser011::InitiateGameConnection(void * a1, int a2, CSteamID a3, unsigned int a4, unsigned short a5, bool a6)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u / %u, %u, %u, %u, %u)\n", __FUNCTION__, a2, a3.m_unAccountID, a4, a5, a6); 
	}
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->InitiateGameConnection(a1, a2, a3, a4, a5, a6); 
}
void CSteamUser011::TerminateGameConnection(unsigned int a1, unsigned short a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TerminateGameConnection(a1, a2); 
}
void CSteamUser011::TrackAppUsageEvent(CGameID a1, int a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TrackAppUsageEvent(a1, a2, a3); 
}
int CSteamUser011::GetUserDataFolder(char * a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetUserDataFolder(a1, a2); 
}
int CSteamUser011::StartVoiceRecording(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->StartVoiceRecording(); 
}
int CSteamUser011::StopVoiceRecording(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->StopVoiceRecording(); 
}
int CSteamUser011::GetCompressedVoice(void * a1, unsigned int a2, unsigned int * a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetCompressedVoice(a1, a2, a3); 
}
int CSteamUser011::DecompressVoice(void * a1, unsigned int a2, void * a3, unsigned int a4, unsigned int * a5)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->DecompressVoice(a1, a2, a3, a4, a5); 
}
