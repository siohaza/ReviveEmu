class CSteamGameServer003
{
public:
	CSteamGameServer003();
	~CSteamGameServer003();

	virtual void LogOn(void);
	virtual void LogOff(void);
	virtual bool BLoggedOn(void);
	virtual bool BSecure(void);
	virtual CSteamID GetSteamID(void);
	virtual bool GSGetSteam2GetEncryptionKeyToSendToNewClient(void * a1, unsigned int * a2, unsigned int a3);
	virtual bool GSSendUserConnect(unsigned int a1, unsigned int a2, unsigned short a3, void  const* a4, unsigned int a5);
	virtual bool GSRemoveUserConnect(unsigned int a1);
	virtual bool GSSendUserDisconnect(CSteamID a1, unsigned int a2);
	virtual void GSSetSpawnCount(unsigned int a1);
	virtual int GSSetServerType(int a1, unsigned int a2, unsigned int a3, unsigned short a4, unsigned short a5, unsigned short a6, char  const* a7, char  const* a8, bool a9);
	virtual bool GSUpdateStatus(int a1, int a2, int a3, char  const* a4, char  const* a5, char  const* a6);
	virtual bool GSCreateUnauthenticatedUser(CSteamID * a1);
	virtual bool GSSetUserData(CSteamID a1, char  const* a2, unsigned int a3);
	virtual void GSUpdateSpectatorPort(unsigned short a1);
	virtual void GSSetGameType(char  const* a1);
	virtual bool GSSendSteam2UserConnect(unsigned int a1, void  const* a2, unsigned int a3, unsigned int a4, unsigned short a5, void  const* a6, unsigned int a7);
	virtual bool GSSendSteam3UserConnect(CSteamID a1, unsigned int a2, void  const* a3, unsigned int a4);
};