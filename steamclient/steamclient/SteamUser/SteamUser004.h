#include "..\Common\steamclientpublic.h"
#include ".\SteamUser.h"

class CSteamUser004
{
public:
	CSteamUser004();
	~CSteamUser004();

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
	virtual int NClientGameIDAdd(int a1);
	virtual int RemoveClientGame(int a1);
	virtual void SetClientGameServer(int a1, unsigned int a2, unsigned short a3);
	virtual void SetSteam2Ticket(unsigned char * a1, int a2);
	virtual void AddServerNetAddress(unsigned int a1, unsigned short a2);
	virtual void SetEmail(char  const* a1);
	virtual int GetSteamGameConnectToken(void * a1, int a2);
	virtual void SetRegistryString(ERegistrySubTree a1, char  const* a2, char  const* a3);
	virtual void GetRegistryString(ERegistrySubTree a1, char  const* a2, char * a3, int a4);
	virtual void SetRegistryInt(ERegistrySubTree a1, char  const* a2, int a3);
	virtual void GetRegistryInt(ERegistrySubTree a1, char  const* a2, int * a3);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7);
	virtual void TerminateGameConnection(unsigned int a1, unsigned short a2);
	virtual void SetSelfAsPrimaryChatDestination(void);
	virtual void IsPrimaryChatDestination(void);
	virtual void RequestLegacyCDKey(unsigned int a1);
};