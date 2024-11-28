class CSteamApps001
{
public:
	CSteamApps001();
	~CSteamApps001();

	virtual int GetAppData( uint32 nAppID, const char *pchKey, char *pchValue, int cchValueMax );
};