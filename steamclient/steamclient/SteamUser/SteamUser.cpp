#include "..\Common\commonincludes.h"
#include ".\SteamUser.h"
#include <vector>

CSteamUser* g_pSteamUser;
extern DWORD g_dwClientId;
extern std::vector<CallbackMsg_t*> g_CallbackMsgList;

CSteamUser::CSteamUser()
{
}

CSteamUser::~CSteamUser()
{
}

HSteamUser CSteamUser::GetHSteamUser(void)
{
	return 1;
}
void CSteamUser::LogOn(CSteamID a1)
{
}
void CSteamUser::LogOff(void)
{
}
bool CSteamUser::BLoggedOn(void)
{
	return true;
}
void CSteamUser::GetLogonState(void)
{
}
bool CSteamUser::BConnected(void)
{
	return true;
}
CSteamID CSteamUser::GetSteamID(void)
{
	CSteamID a;
	a.FullSet(5, k_EUniversePublic, k_EAccountTypeIndividual);
	return a;
}
bool CSteamUser::IsVACBanned(int a1)
{
	return false;
}
void CSteamUser::RequireShowVACBannedMessage(int a1)
{
}
void CSteamUser::AcknowledgeVACBanning(int a1)
{
}
void CSteamUser::SetSteam2Ticket(unsigned char * a1, int a2)
{
}
void CSteamUser::AddServerNetAddress(unsigned int a1, unsigned short a2)
{
}
void CSteamUser::SetEmail(char  const* a1)
{
}
void CSteamUser::SetRegistryString(ERegistrySubTree, char  const* a1, char  const* a2)
{
}
void CSteamUser::GetRegistryString(ERegistrySubTree, char  const* a1, char *a2, int a3)
{
}
void CSteamUser::SetRegistryInt(ERegistrySubTree, char  const* a1, int a2)
{
}
void CSteamUser::GetRegistryInt(ERegistrySubTree, char  const* a1, int * a2)
{
}
int CSteamUser::InitiateGameConnection( void *pBlob, int cbMaxBlob, CSteamID steamID, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure, void *pvSteam2GetEncryptionKey, int cbSteam2GetEncryptionKey ) 
{
	CTicket _ticket;
	_ticket.m_Signature = 0x00726576;
	_ticket.m_UserID = g_dwClientId;
	_ticket.m_Version = 9;
	memcpy(pBlob, &_ticket, sizeof(CTicket));
	return 1;
}
int CSteamUser::InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7)
{
	CTicket _ticket;
	_ticket.m_Signature = 0x00726576;
	_ticket.m_UserID = g_dwClientId;
	_ticket.m_Version = 9;
	memcpy(a1, &_ticket, sizeof(CTicket));
	return 1;
}
void CSteamUser::TerminateGameConnection(unsigned int a1, unsigned short a2)
{
}
void CSteamUser::SetSelfAsPrimaryChatDestination(void)
{
}
void CSteamUser::IsPrimaryChatDestination(void)
{
}
void CSteamUser::RequestLegacyCDKey(unsigned int a1)
{
}
void CSteamUser::SendGuestPassByEmail(char  const* a1, unsigned long long a2, bool a3)
{
}
void CSteamUser::SendGuestPassByAccountID(unsigned int a1, unsigned long long a2, bool a3)
{
}
void CSteamUser::AckGuestPass(char  const* a1)
{
}
void CSteamUser::RedeemGuestPass(char  const* a1)
{
}
void CSteamUser::GetGuestPassToGiveCount(void)
{
}
void CSteamUser::GetGuestPassToRedeemCount(void)
{
}
void CSteamUser::GetGuestPassLastUpdateTime(void)
{
}
void CSteamUser::GetGuestPassToGiveInfo(unsigned int a1, unsigned long long * a2, int * a3, unsigned int * a4, unsigned int * a5, unsigned int * a6, unsigned int * a7, char * a8, int a9)
{
}
void CSteamUser::GetGuestPassToRedeemInfo(unsigned int a1, unsigned long long * a2, int * a3, unsigned int * a4, unsigned int * a5, unsigned int * a6, unsigned int * a7)
{
}
void CSteamUser::GetGuestPassToRedeemSenderAddress(unsigned int a1, char * a2, int a3)
{
}
void CSteamUser::GetGuestPassToRedeemSenderName(unsigned int a1, char * a2, int a3)
{
}
void CSteamUser::AcknowledgeMessageByGID(char  const* a1)
{
}
void CSteamUser::SetLanguage(char  const* a1)
{
}
void CSteamUser::TrackAppUsageEvent(CGameID a1, int a2, char  const* a3)
{
}
void CSteamUser::SetAccountName(char  const* a1)
{
}
void CSteamUser::SetPassword(char  const* a1)
{
}
void CSteamUser::SetAccountCreationTime(unsigned int a1)
{
}
void CSteamUser::RefreshSteam2Login(void)
{
}
int CSteamUser::InitiateGameConnection(void * a1, int a2, CSteamID a3, unsigned int a4, unsigned short a5, bool a6)
{
	return 1;
}
int CSteamUser::GetUserDataFolder(char * a1, int a2)
{
	strcpy(a1, "");
	return 0;	
}
int CSteamUser::StartVoiceRecording(void)
{
	return 0;
}
int CSteamUser::StopVoiceRecording(void)
{
	return 0;
}
int CSteamUser::GetCompressedVoice(void * a1, unsigned int a2, unsigned int * a3)
{
	*a3 = 0;
	return 0;
}
int CSteamUser::DecompressVoice(void * a1, unsigned int a2, void * a3, unsigned int a4, unsigned int * a5)
{
	*a5 = 0;
	return 0;
}


CSteamUser* GSteamUser(void)
{
	static CSteamUser g_SteamUser;
	return &g_SteamUser;
}

int CSteamUser::NClientGameIDAdd(int a1)
{
	return 1;
}

int CSteamUser::RemoveClientGame(int a1)
{
	return 1;
}

void CSteamUser::SetClientGameServer(int a1, unsigned int a2, unsigned short a3)
{
}
	
int CSteamUser::GetSteamGameConnectToken(void * a1, int a2)
{
	return 0;
}
