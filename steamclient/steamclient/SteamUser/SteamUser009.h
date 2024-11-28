class CSteamUser009
{
public:
	CSteamUser009();
	~CSteamUser009();

	virtual HSteamUser GetHSteamUser(void);
	virtual bool BLoggedOn(void);
	virtual CSteamID GetSteamID(void);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, CGameID a4, unsigned int a5, unsigned short a6, bool a7, void * a8, int a9);
	virtual void TerminateGameConnection(unsigned int a1, unsigned short a2);
	virtual void TrackAppUsageEvent(CGameID a1, int a2, char  const* a3);
	virtual void RefreshSteam2Login(void);
};