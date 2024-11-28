class CSteamUser011
{
public:
	CSteamUser011();
	~CSteamUser011();

	virtual HSteamUser GetHSteamUser(void);
	virtual bool BLoggedOn(void);
	virtual CSteamID GetSteamID(void);
	virtual int InitiateGameConnection(void * a1, int a2, CSteamID a3, unsigned int a4, unsigned short a5, bool a6);
	virtual void TerminateGameConnection(unsigned int a1, unsigned short a2);
	virtual void TrackAppUsageEvent(CGameID a1, int a2, char  const* a3);
	virtual int GetUserDataFolder(char * a1, int a2);
	virtual int StartVoiceRecording(void);
	virtual int StopVoiceRecording(void);
	virtual int GetCompressedVoice(void * a1, unsigned int a2, unsigned int * a3);
	virtual int DecompressVoice(void * a1, unsigned int a2, void * a3, unsigned int a4, unsigned int * a5);
};