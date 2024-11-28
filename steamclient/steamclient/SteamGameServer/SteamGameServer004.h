class CSteamGameServer004
{
public:
	CSteamGameServer004();
	~CSteamGameServer004();

	virtual void LogOn(void);
	virtual void LogOff(void);
	virtual bool BLoggedOn(void);
	virtual bool BSecure(void);
	virtual CSteamID GetSteamID(void);
	virtual int SendUserConnectAndAuthenticate(CSteamID a1, unsigned int a2, void * a3, unsigned int a4);
	virtual CSteamID CreateUnauthenticatedUserConnection(void);
	virtual bool GSSendUserDisconnect(CSteamID a1, unsigned int a2);
	virtual bool BUpdateUserData(CSteamID a1, char  const* a2, unsigned int a3);
	virtual int BSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned short a4, unsigned short a5, unsigned short a6, char  const* a7, char  const* a8, bool a9);
	virtual bool UpdateServerStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6);
	virtual void UpdateSpectatorPort(unsigned short a1);
	virtual void SetGameType(char  const* a1);
	virtual bool BGetUserAchievementStatus(CSteamID a1, char  const* a2);
};