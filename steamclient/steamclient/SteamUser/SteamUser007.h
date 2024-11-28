#include ".\SteamUser.h"

class CSteamUser007
{
public:
	CSteamUser007();
	~CSteamUser007();

	virtual HSteamUser GetHSteamUser(void);
	virtual void LogOn(CSteamID a1);
	virtual void LogOff(void);
	virtual bool BLoggedOn(void);
	virtual CSteamID GetSteamID(void);
	virtual void SetRegistryString(ERegistrySubTree a1, char  const* a2, char  const* a3);
	virtual void GetRegistryString(ERegistrySubTree a1, char  const* a2, char * a3, int a4);
	virtual void SetRegistryInt(ERegistrySubTree a1, char  const* a2, int a3);
	virtual void GetRegistryInt(ERegistrySubTree a1, char  const* a2, int * a3);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7, void * a8, int a9);
	virtual void TerminateGameConnection(unsigned int a1, unsigned short a2);
	virtual void TrackAppUsageEvent(CGameID a1, int a2, char  const* a3);
	virtual void RefreshSteam2Login(void);
};
