#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUser004.h"
#include ".\SteamUser.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUser* g_pSteamUser;

CSteamUser004::CSteamUser004()
{
}

CSteamUser004::~CSteamUser004()
{
}

HSteamUser CSteamUser004::GetHSteamUser(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetHSteamUser(); 
}
void CSteamUser004::LogOn(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->LogOn(a1); 
}
void CSteamUser004::LogOff(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->LogOff(); 
}
bool CSteamUser004::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->BLoggedOn(); 
}
void CSteamUser004::GetLogonState(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetLogonState(); 
}
bool CSteamUser004::BConnected(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->BConnected(); 
}
CSteamID CSteamUser004::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetSteamID(); 
}
bool CSteamUser004::IsVACBanned(int a1)
{
	//if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->IsVACBanned(a1); 
}
void CSteamUser004::RequireShowVACBannedMessage(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->RequireShowVACBannedMessage(a1); 
}
void CSteamUser004::AcknowledgeVACBanning(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->AcknowledgeVACBanning(a1); 
}
int CSteamUser004::NClientGameIDAdd(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	//g_pSteamUser = GSteamUser();
	//return g_pSteamUser->NClientGameIDAdd(a1); 
	return 0;
}
int CSteamUser004::RemoveClientGame(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	//g_pSteamUser = GSteamUser();
	//return g_pSteamUser->RemoveClientGame(a1); 
	return 0;
}
void CSteamUser004::SetClientGameServer(int a1, unsigned int a2, unsigned short a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	//g_pSteamUser = GSteamUser();
	//return g_pSteamUser->SetClientGameServer(a1, a2, a3); 
}
void CSteamUser004::SetSteam2Ticket(unsigned char * a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetSteam2Ticket(a1, a2); 
}
void CSteamUser004::AddServerNetAddress(unsigned int a1, unsigned short a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->AddServerNetAddress(a1, a2); 
}
void CSteamUser004::SetEmail(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetEmail(a1); 
}
int CSteamUser004::GetSteamGameConnectToken(void * a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	//g_pSteamUser = GSteamUser();
	//return g_pSteamUser->GetSteamGameConnectToken(a1, a2); 
	return 0;
}
void CSteamUser004::SetRegistryString(ERegistrySubTree a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetRegistryString(a1, a2, a3); 
}
void CSteamUser004::GetRegistryString(ERegistrySubTree a1, char  const* a2, char * a3, int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetRegistryString(a1, a2, a3, a4); 
}
void CSteamUser004::SetRegistryInt(ERegistrySubTree a1, char  const* a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetRegistryInt(a1, a2, a3); 
}
void CSteamUser004::GetRegistryInt(ERegistrySubTree a1, char  const* a2, int * a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetRegistryInt(a1, a2, a3); 
}
int CSteamUser004::InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u / %u, %u, %u, %u, %u)\n", __FUNCTION__, a2, a3.m_unAccountID, a4.AppID(), a5, a6, a7); 
	}
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->InitiateGameConnection(a1, a2, a3, a4, a5, a6, a7); 
}
void CSteamUser004::TerminateGameConnection(unsigned int a1, unsigned short a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TerminateGameConnection(a1, a2); 
}
void CSteamUser004::SetSelfAsPrimaryChatDestination(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetSelfAsPrimaryChatDestination(); 
}
void CSteamUser004::IsPrimaryChatDestination(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->IsPrimaryChatDestination(); 
}
void CSteamUser004::RequestLegacyCDKey(unsigned int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->RequestLegacyCDKey(a1); 
}

