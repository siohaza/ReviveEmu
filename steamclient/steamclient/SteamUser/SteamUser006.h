#include ".\SteamUser.h"

class CSteamUser006
{
public:
	CSteamUser006();
	~CSteamUser006();

	virtual HSteamUser GetHSteamUser(void);
	virtual void LogOn(CSteamID a1);
	virtual void LogOff(void);
	virtual bool BLoggedOn(void);
	virtual CSteamID GetSteamID(void);
	virtual void SetRegistryString(ERegistrySubTree a1, char  const* a2, char  const* a3);
	virtual void GetRegistryString(ERegistrySubTree a1, char  const* a2, char * a3, int a4);
	virtual void SetRegistryInt(ERegistrySubTree a1, char  const* a2, int a3);
	virtual void GetRegistryInt(ERegistrySubTree a1, char  const* a2, int * a3);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7);
	virtual void TerminateGameConnection(unsigned int a1, unsigned short a2);
	virtual void TrackAppUsageEvent(CGameID a1, int a2, char  const* a3);
};
