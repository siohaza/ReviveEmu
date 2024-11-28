#pragma once

#include "..\Common\steamclientpublic.h"

class CSteamApps
{
public:
	CSteamApps();
	~CSteamApps();

	virtual int GetAppData( uint32 nAppID, const char *pchKey, char *pchValue, int cchValueMax );
	virtual bool BIsSubscribed(void);
	virtual bool BIsLowViolence(void);
	virtual bool BIsCybercafe(void);
	virtual bool BIsVACBanned(void);
	virtual unsigned char* GetCurrentGameLanguage(void);
	virtual unsigned char* GetAvailableGameLanguages(void);
	virtual bool BIsSubscribedApp(unsigned int iAppID);
};

CSteamApps* GSteamApps(void);