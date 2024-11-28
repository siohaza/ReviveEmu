class CSteamApps002
{
public:
	CSteamApps002();
	~CSteamApps002();

	virtual bool BIsSubscribed(void);
	virtual bool BIsLowViolence(void);
	virtual bool BIsCybercafe(void);
	virtual bool BIsVACBanned(void);
	virtual unsigned char* GetCurrentGameLanguage(void);
	virtual unsigned char* GetAvailableGameLanguages(void);
	virtual bool BIsSubscribedApp(unsigned int iAppID);
};