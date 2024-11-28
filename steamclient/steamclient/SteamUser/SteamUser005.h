#include ".\SteamUser.h"

class CSteamUser005
{
public:
	CSteamUser005();
	~CSteamUser005();

	virtual HSteamUser GetHSteamUser(void);
	virtual void LogOn(CSteamID a1);
	virtual void LogOff(void);
	virtual bool BLoggedOn(void);
	virtual void GetLogonState(void);
	virtual bool BConnected(void);
	virtual CSteamID GetSteamID(void);
	virtual bool IsVACBanned(int a1);
	virtual void RequireShowVACBannedMessage(int a1);
	virtual void AcknowledgeVACBanning(int a1);
	virtual void SetSteam2Ticket(unsigned char * a1, int a2);
	virtual void AddServerNetAddress(unsigned int a1, unsigned short a2);
	virtual void SetEmail(char  const* a1);
	virtual void SetRegistryString(ERegistrySubTree a1, char  const* a2, char  const* a3);
	virtual void GetRegistryString(ERegistrySubTree a1, char  const* a2, char * a3, int a4);
	virtual void SetRegistryInt(ERegistrySubTree a1, char  const* a2, int a3);
	virtual void GetRegistryInt(ERegistrySubTree a1, char  const* a2, int * a3);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7);
	virtual void TerminateGameConnection(unsigned int a1, unsigned short a2);
	virtual void SetSelfAsPrimaryChatDestination(void);
	virtual void IsPrimaryChatDestination(void);
	virtual void RequestLegacyCDKey(unsigned int a1);
	virtual void SendGuestPassByEmail(char  const* a1, unsigned long long a2, bool a3);
	virtual void SendGuestPassByAccountID(unsigned int a1, unsigned long long a2, bool a3);
	virtual void AckGuestPass(char  const* a1);
	virtual void RedeemGuestPass(char  const* a1);
	virtual void GetGuestPassToGiveCount(void);
	virtual void GetGuestPassToRedeemCount(void);
	virtual void GetGuestPassLastUpdateTime(void);
	virtual void GetGuestPassToGiveInfo(unsigned int a1, unsigned long long * a2, int * a3, unsigned int * a4, unsigned int * a5, unsigned int * a6, unsigned int * a7, char * a8, int a9);
	virtual void GetGuestPassToRedeemInfo(unsigned int a1, unsigned long long * a2, int * a3, unsigned int * a4, unsigned int * a5, unsigned int * a6, unsigned int * a7);
	virtual void GetGuestPassToRedeemSenderAddress(unsigned int a1, char * a2, int a3);
	virtual void GetGuestPassToRedeemSenderName(unsigned int a1, char * a2, int a3);
	virtual void AcknowledgeMessageByGID(char  const* a1);
	virtual void SetLanguage(char  const* a1);
	virtual void TrackAppUsageEvent(CGameID a1, int a2, char  const* a3);
	virtual void SetAccountName(char  const* a1);
	virtual void SetPassword(char  const* a1);
	virtual void SetAccountCreationTime(unsigned int a1);
};
