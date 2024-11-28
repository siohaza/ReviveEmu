class CSteamGameServer007
{
public:
	CSteamGameServer007();
	~CSteamGameServer007();

	virtual int LogOn(void);
	virtual int LogOff(void);
	virtual bool BLoggedOn(void);
	virtual bool BSecure(void);
	virtual CSteamID GetSteamID(void);
	virtual int SendUserConnectAndAuthenticate(unsigned int a1, void  const* a2, unsigned int a3, CSteamID * a4);
	virtual CSteamID CreateUnauthenticatedUserConnection(void);
	virtual bool GSSendUserDisconnect(CSteamID a1);
	virtual bool BUpdateUserData(CSteamID a1, char  const* a2, unsigned int a3);
	virtual int BSetServerType(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned short a5, char  const* a6, char  const* a7, bool a8);
	virtual bool UpdateServerStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6);
	virtual void UpdateSpectatorPort(unsigned short a1);
	virtual void SetGameType(char  const* a1);
	virtual bool BGetUserAchievementStatus(CSteamID a1, char  const* a2);
	virtual int GetGameplayStats(void);
	virtual int RequestUserGroupStatus(CSteamID a1, CSteamID a2);
};