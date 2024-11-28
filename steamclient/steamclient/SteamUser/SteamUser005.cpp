#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamUser005.h"
#include ".\SteamUser.h"

extern bool g_bLogging;
extern CLogFile* Logger;
extern CSteamUser* g_pSteamUser;

CSteamUser005::CSteamUser005()
{
}

CSteamUser005::~CSteamUser005()
{
}

HSteamUser CSteamUser005::GetHSteamUser(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetHSteamUser(); 
}
void CSteamUser005::LogOn(CSteamID a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->LogOn(a1); 
}
void CSteamUser005::LogOff(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->LogOff(); 
}
bool CSteamUser005::BLoggedOn(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->BLoggedOn(); 
}
void CSteamUser005::GetLogonState(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetLogonState(); 
}
bool CSteamUser005::BConnected(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->BConnected(); 
}
CSteamID CSteamUser005::GetSteamID(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetSteamID(); 
}
bool CSteamUser005::IsVACBanned(int a1)
{
	//if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->IsVACBanned(a1); 
}
void CSteamUser005::RequireShowVACBannedMessage(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->RequireShowVACBannedMessage(a1); 
}
void CSteamUser005::AcknowledgeVACBanning(int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->AcknowledgeVACBanning(a1); 
}
void CSteamUser005::SetSteam2Ticket(unsigned char * a1, int a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetSteam2Ticket(a1, a2); 
}
void CSteamUser005::AddServerNetAddress(unsigned int a1, unsigned short a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->AddServerNetAddress(a1, a2); 
}
void CSteamUser005::SetEmail(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetEmail(a1); 
}
void CSteamUser005::SetRegistryString(ERegistrySubTree a1, char  const* a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetRegistryString(a1, a2, a3); 
}
void CSteamUser005::GetRegistryString(ERegistrySubTree a1, char  const* a2, char * a3, int a4)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetRegistryString(a1, a2, a3, a4); 
}
void CSteamUser005::SetRegistryInt(ERegistrySubTree a1, char  const* a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetRegistryInt(a1, a2, a3); 
}
void CSteamUser005::GetRegistryInt(ERegistrySubTree a1, char  const* a2, int * a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetRegistryInt(a1, a2, a3); 
}
int CSteamUser005::InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7)
{
	if (g_bLogging) 
	{
		Logger->Write("%s (%u / %u, %u, %u, %u, %u)\n", __FUNCTION__, a2, a3.m_unAccountID, a4.AppID(), a5, a6, a7); 
	}
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->InitiateGameConnection(a1, a2, a3, a4, a5, a6, a7); 
}
void CSteamUser005::TerminateGameConnection(unsigned int a1, unsigned short a2)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TerminateGameConnection(a1, a2); 
}
void CSteamUser005::SetSelfAsPrimaryChatDestination(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetSelfAsPrimaryChatDestination(); 
}
void CSteamUser005::IsPrimaryChatDestination(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->IsPrimaryChatDestination(); 
}
void CSteamUser005::RequestLegacyCDKey(unsigned int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->RequestLegacyCDKey(a1); 
}
void CSteamUser005::SendGuestPassByEmail(char  const* a1, unsigned long long a2, bool a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SendGuestPassByEmail(a1, a2, a3); 
}
void CSteamUser005::SendGuestPassByAccountID(unsigned int a1, unsigned long long a2, bool a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SendGuestPassByAccountID(a1, a2, a3); 
}
void CSteamUser005::AckGuestPass(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->AckGuestPass(a1); 
}
void CSteamUser005::RedeemGuestPass(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->RedeemGuestPass(a1); 
}
void CSteamUser005::GetGuestPassToGiveCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetGuestPassToGiveCount(); 
}
void CSteamUser005::GetGuestPassToRedeemCount(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetGuestPassToRedeemCount(); 
}
void CSteamUser005::GetGuestPassLastUpdateTime(void)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetGuestPassLastUpdateTime(); 
}
void CSteamUser005::GetGuestPassToGiveInfo(unsigned int a1, unsigned long long * a2, int * a3, unsigned int * a4, unsigned int * a5, unsigned int * a6, unsigned int * a7, char * a8, int a9)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetGuestPassToGiveInfo(a1, a2, a3, a4, a5, a6, a7, a8, a9); 
}
void CSteamUser005::GetGuestPassToRedeemInfo(unsigned int a1, unsigned long long * a2, int * a3, unsigned int * a4, unsigned int * a5, unsigned int * a6, unsigned int * a7)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetGuestPassToRedeemInfo(a1, a2, a3, a4, a5, a6, a7); 
}
void CSteamUser005::GetGuestPassToRedeemSenderAddress(unsigned int a1, char * a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetGuestPassToRedeemSenderAddress(a1, a2, a3); 
}
void CSteamUser005::GetGuestPassToRedeemSenderName(unsigned int a1, char * a2, int a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->GetGuestPassToRedeemSenderName(a1, a2, a3); 
}
void CSteamUser005::AcknowledgeMessageByGID(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->AcknowledgeMessageByGID(a1); 
}
void CSteamUser005::SetLanguage(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetLanguage(a1); 
}
void CSteamUser005::TrackAppUsageEvent(CGameID a1, int a2, char  const* a3)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->TrackAppUsageEvent(a1, a2, a3); 
}
void CSteamUser005::SetAccountName(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetAccountName(a1); 
}
void CSteamUser005::SetPassword(char  const* a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetPassword(a1); 
}
void CSteamUser005::SetAccountCreationTime(unsigned int a1)
{
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamUser = GSteamUser();
	return g_pSteamUser->SetAccountCreationTime(a1); 
}
