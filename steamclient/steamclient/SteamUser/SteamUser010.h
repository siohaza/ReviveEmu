class CSteamUser010
{
public:
	CSteamUser010();
	~CSteamUser010();

	virtual HSteamUser GetHSteamUser(void);
	virtual bool BLoggedOn(void);
	virtual CSteamID GetSteamID(void);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, unsigned int a4, unsigned short a5, bool a6);
	virtual void TerminateGameConnection(unsigned int a1, unsigned short a2);
	virtual void TrackAppUsageEvent(CGameID a1, int a2, char  const* a3);
};